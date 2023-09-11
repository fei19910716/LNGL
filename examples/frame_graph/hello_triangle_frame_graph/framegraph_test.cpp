#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstddef>

#include "base/frame_graph/framegraph.hpp"
#include "base/renderer/texture_quad_renderer.h"
#include "base/renderer/triangle_renderer.h"
#include "base/renderer/gaussian_blur_renderer.h"
#include "base/renderer/present_renderer.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Renderer* texture_renderer;
Renderer* triagnle_renderer;
Renderer* blur_renderer;
Renderer* present_renderer;

// callbacks
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void init()
{
    texture_renderer = new TextureQuadRenderer("4.1.texture.vs","4.1.texture.fs","resources/textures/awesomeface.png");
    triagnle_renderer = new TriangleRenderer("3.3.shader.vs","3.3.shader.fs");
    blur_renderer = new GuassianBlurRenderer("gaussian_blur.vs","gaussian_blur.fs");
    present_renderer = new PresentRenderer("present.vs","present.fs");
}


void render()
{
    fg::framegraph framegraph;

    auto retained_resource = framegraph.add_retained_resource("Backbuffer", 
                                                              FrameBuffer::Description(), 
                                                              new FrameBuffer);

    // 1st render task declaration.
    struct render_task_0_data
    {
      fbo_resource* output;
    };
    auto render_task_0 = framegraph.add_render_task<render_task_0_data>(
    "Clear Pass",
    [&] (render_task_0_data& data, fg::render_task_builder& builder)
    {
      FrameBuffer::Description desc;
      {
        desc.width = SCR_WIDTH;
        desc.height = SCR_HEIGHT;
        desc.color_format = GL_RGBA;
        desc.depth_format = GL_DEPTH24_STENCIL8;
      }

      data.output = builder.create<fbo_resource>("FBO",desc);
    },
    [=] (const render_task_0_data& data)
    {
      data.output->actual()->Bind();

      glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

    });
    auto& data_0 = render_task_0->data();


    // // 2st render task declaration.
    struct render_task_1_data
    {
      fbo_resource* output;
    };
    auto render_task_1 = framegraph.add_render_task<render_task_1_data>(
    "Texture Pass",
    [&] (render_task_1_data& data, fg::render_task_builder& builder)
    {
      data.output = builder.write<fbo_resource>(data_0.output);
    },
    [=] (const render_task_1_data& data)
    {
      data.output->actual()->Bind();

      texture_renderer->render();

    });

    auto& data_1 = render_task_1->data();


    // 3st render task declaration.
    struct render_task_2_data
    {
      fbo_resource* output;
    };
    auto render_task_2 = framegraph.add_render_task<render_task_2_data>(
    "Triangle Pass",
    [&] (render_task_2_data& data, fg::render_task_builder& builder)
    {
      data.output = builder.write<fbo_resource>(data_1.output);
    },
    [=] (const render_task_2_data& data)
    {
      data.output->actual()->Bind();
      
      triagnle_renderer->render();

    });

    auto& data_2 = render_task_2->data();

    // 4st render task declaration.
    struct blur_data
    {
      fbo_resource* input;
      fbo_resource* output;
    };
    auto blur_task = framegraph.add_render_task<blur_data>(
    "Blur Pass",
    [&] (blur_data& data, fg::render_task_builder& builder)
    {
      data.input = builder.read<fbo_resource>(data_2.output);
      data.output = builder.write<fbo_resource>(data_2.output);
    },
    [=] (const blur_data& data)
    {
      
      data.output->actual()->Bind();
      data.input->actual()->BindColor(GL_TEXTURE0);
      blur_renderer->render();

    });

    auto& blur_out_data = blur_task->data();

    // 4st render task declaration.
    struct present_data
    {
      fbo_resource* input;
      fbo_resource* output;
    };
    auto present_task = framegraph.add_render_task<present_data>(
    "Present Pass",
    [&] (present_data& data, fg::render_task_builder& builder)
    {
      data.input = builder.read<fbo_resource>(data_1.output);
      data.output = builder.write<fbo_resource>(retained_resource);
    },
    [=] (const present_data& data)
    {
      
      data.output->actual()->Bind();
      
      data.input->actual()->BindColor(GL_TEXTURE0);
      present_renderer->render();

    });

    framegraph.compile();
    framegraph.execute();
    framegraph.clear();
}



void clean()
{
    delete triagnle_renderer;
}


ExamleMain("hello_triangle_frame_graph", SCR_WIDTH, SCR_HEIGHT)