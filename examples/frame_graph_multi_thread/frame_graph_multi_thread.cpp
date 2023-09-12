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
TextureQuadRenderer* texture_renderer;
TriangleRenderer* triagnle_renderer;
GuassianBlurRenderer* blur_renderer;
PresentRenderer* present_renderer;

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
    texture_renderer = new TextureQuadRenderer("texture.vs","texture.fs","resources/textures/awesomeface.png");
    triagnle_renderer = new TriangleRenderer("triangle.vs","triangle.fs");
    blur_renderer = new GuassianBlurRenderer("gaussian_blur.vs","gaussian_blur.fs");
    present_renderer = new PresentRenderer("present.vs","present.fs");
}


void render()
{
    fg::framegraph framegraph;

    auto back_buffer = framegraph.add_retained_resource("Backbuffer", 
                                                        FrameBuffer::Description(), 
                                                        new FrameBuffer);

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
        desc.width = SCR_WIDTH;
        desc.height = SCR_HEIGHT;
        desc.color_format = GL_RGBA;
        desc.depth_format = GL_DEPTH24_STENCIL8;
      }

      data.output = builder.create<fbo_resource>("FBO",desc);
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


    // 3st render task declaration.
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

    // 4st render task declaration.
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
      data.output = builder.write<fbo_resource>(triangle_pass_out_data.output);
    },
    [=] (const blur_pass_data& data)
    {
      
      data.output->actual()->Bind();
      data.input->actual()->BindColor(GL_TEXTURE0);
      blur_renderer->render();

    });

    auto& blur_pass_out_data = blur_pass_task->data();

    // 4st render task declaration.
    struct present_pass_data
    {
      fbo_resource* input;
      fbo_resource* output;
    };
    auto present_pass_task = framegraph.add_render_task<present_pass_data>(
    "Present Pass",
    [&] (present_pass_data& data, fg::render_task_builder& builder)
    {
      data.input = builder.read<fbo_resource>(blur_pass_out_data.output);
      data.output = builder.write<fbo_resource>(back_buffer);
    },
    [=] (const present_pass_data& data)
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


ExamleMain("frame_graph_multi_thread", SCR_WIDTH, SCR_HEIGHT)