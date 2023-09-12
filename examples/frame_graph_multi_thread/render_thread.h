
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

struct Message
{
   glm::mat4 player_model;
   int value = 0;
};

#define SIZE 3

template<typename T>
struct Container
{
    T arr[SIZE];
    int start = 0;
    int end   = 0;

    void pop()
    {
        for(int i = start; i< end; i++){
            arr[start] = arr[start + 1];
        }

        end--;
    }

    void push(T& t)
    {
        if(start == end){
            arr[start] = t;
            end++;
        }else{
            arr[end] = t;
            end++;
        }
    }

    T front()
    {
        return arr[start];
    }

    bool empty()
    {
        return start == end;
    }

    bool full()
    {
        return start == 0 && end == SIZE - 1;
    }
};


struct MessageQueue
{
    std::atomic<Container<Message*>> queue; // global variable

    std::mutex mtx;
    std::unique_lock<std::mutex> lock;
    std::condition_variable cv;

    Message* pop()
    {
        Message* msg;

        Container<Message*> s = queue.load();
        Container<Message*> new_s;
        do {
            
            new_s = s;
            if(new_s.empty()){
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock);
                std::cout << "message is empty" << std::endl;
            }
            
            msg = new_s.front();
                new_s.pop();
        } while (!queue.compare_exchange_strong(s, new_s));
        cv.notify_one();
        return msg;
    }

    void push(Message* message)
    {
        Container<Message*> s = queue.load();
        Container<Message*> new_s;
        do {
            new_s = s;

            if(new_s.full()){
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock);

                std::cout << "message is full" << std::endl;
            }
            
            new_s.push(message);
        } while (!queue.compare_exchange_strong(s, new_s));

        cv.notify_one();
    }
};

struct TextureQueue
{
    std::atomic<Container<unsigned int>> queue;
    std::mutex mtx;
    std::unique_lock<std::mutex> lock;
    std::condition_variable cv;

    unsigned int pop()
    {
        unsigned int id = GL_INVALID_VALUE;

        Container<unsigned int> s = queue.load();
        Container<unsigned int> new_s;
        do {
            new_s = s;
            
            if(new_s.empty()){
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock);
                std::cout << "texture is empty" << std::endl;
            }
            
            id = new_s.front();
                new_s.pop();
        } while (!queue.compare_exchange_strong(s, new_s));
        cv.notify_one();
        return id;
    }

    void push(unsigned int message)
    {
        Container<unsigned int> s = queue.load();
        Container<unsigned int> new_s;
        do {
            
            new_s = s;
            if(new_s.full()){
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock);
                std::cout << "texture is full" << std::endl;
            }
            
            new_s.push(message);
        } while (!queue.compare_exchange_strong(s, new_s));
        cv.notify_one();
    }
};



class RenderThread
{
public:
    
    std::thread mThread;
    GLFWwindow* offscreen_context;
    unsigned int w, h;
    bool thread_run;

    ~RenderThread()
    {

    }

    void init(GLFWwindow *window, unsigned int w, unsigned h)
    {
        this->w = w;
        this->h = h;
        this->thread_run = false;
        this->offscreen_context = window;
    }

    void start(MessageQueue& message_queue, TextureQueue& texture_queue)
    {
        this->thread_run = true;
        mThread = std::thread(&RenderThread::run,this, std::ref(message_queue), std::ref(texture_queue));
        mThread.detach();
    }

    void stop()
    {
        this->thread_run = false;
    }

    void run(MessageQueue& message_queue, TextureQueue& texture_queue)
    {
        glfwMakeContextCurrent(offscreen_context);

        auto texture_renderer = new TextureQuadRenderer("texture.vs","texture.fs","resources/textures/awesomeface.png");
        auto triagnle_renderer = new TriangleRenderer("triangle.vs","triangle.fs");
        auto blur_renderer = new GuassianBlurRenderer("gaussian_blur.vs","gaussian_blur.fs");
        
        while (this->thread_run)
        {
            // create a color attachment texture
            unsigned int color;
            glGenTextures(1, &color);
            glBindTexture(GL_TEXTURE_2D, color);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            Message* msg = message_queue.pop();
            if(msg == nullptr) continue;

            fg::framegraph framegraph;

            

            FrameBuffer::Description desc;
            {
                desc.width = w;
                desc.height = h;
                desc.color_format = GL_RGBA;
                desc.depth_format = GL_DEPTH24_STENCIL8;
                desc.color_id = color;
            }
            auto back_buffer = framegraph.add_retained_resource("Backbuffer", 
                                                            desc, 
                                                            (FrameBuffer*)nullptr);

            // 1st render task declaration.
            struct clear_pass_data
            {
            fbo_resource* output;
            };
            auto clear_pass_task = framegraph.add_render_task<clear_pass_data>(
            "Clear Pass",
            [&] (clear_pass_data& data, fg::render_task_builder& builder)
            {
            FrameBuffer::Description desc;
            {
                desc.width = w;
                desc.height = h;
                desc.color_format = GL_RGBA;
                desc.depth_format = GL_DEPTH24_STENCIL8;
            }
            data.output = builder.create<fbo_resource>("fbo",desc);
            },
            [=] (const clear_pass_data& data)
            {
            data.output->actual()->Bind();

            glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            });
            auto& clear_pass_out_data = clear_pass_task->data();

                // // 2st render task declaration.
            struct texture_pass_data
            {
            fbo_resource* output;
            };
            auto texture_pass_task = framegraph.add_render_task<texture_pass_data>(
            "Texture Pass",
            [&] (texture_pass_data& data, fg::render_task_builder& builder)
            {
            data.output = builder.write<fbo_resource>(clear_pass_out_data.output);
            },
            [=] (const texture_pass_data& data)
            {
            data.output->actual()->Bind();

            texture_renderer->render();

            });

            auto& texture_pass_out_data = texture_pass_task->data();

            //     // 3st render task declaration.
            struct triangle_pass_data
            {
            fbo_resource* output;
            };
            auto triangle_pass_task = framegraph.add_render_task<triangle_pass_data>(
            "Triangle Pass",
            [&] (triangle_pass_data& data, fg::render_task_builder& builder)
            {
            data.output = builder.write<fbo_resource>(texture_pass_out_data.output);
            },
            [=] (const triangle_pass_data& data)
            {
            data.output->actual()->Bind();
            glm::mat4 model = glm::mat4(1.0f);
                    triagnle_renderer->SetUniform<glm::mat4>("model",model);
            triagnle_renderer->render();

            });

            auto& triangle_pass_out_data = triangle_pass_task->data();


                //     // 4st render task declaration.
            struct blur_pass_data
            {
            fbo_resource* input;
            fbo_resource* output;
            };
            auto blur_pass_task = framegraph.add_render_task<blur_pass_data>(
            "Blur Pass",
            [&] (blur_pass_data& data, fg::render_task_builder& builder)
            {
            data.input = builder.read<fbo_resource>(triangle_pass_out_data.output);
            data.output = builder.write<fbo_resource>(back_buffer);
            },
            [=] (const blur_pass_data& data)
            {
            
            data.output->actual()->Bind();
            data.input->actual()->BindColor(GL_TEXTURE0);
            blur_renderer->render();

            });

            auto& blur_pass_out_data = blur_pass_task->data();


            framegraph.compile();
            framegraph.execute();
            framegraph.clear();

            glFlush();
            texture_queue.push(color);
            delete msg;
        }
    
        std::cout << "thread stop" << std::endl;
    }
};