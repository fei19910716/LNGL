#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstddef>

#include "base/frame_graph/framegraph.hpp"
#include "base/renderer/texture_quad_renderer.h"
#include "base/renderer/triangle_renderer.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Renderer* texture_renderer;
Renderer* triagnle_renderer;

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
}


void render()
{
    fg::framegraph framegraph;

    auto retained_resource = framegraph.add_retained_resource(
    "Backbuffer", 
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
      data.output = builder.write<fbo_resource>(retained_resource);
    },
    [=] (const render_task_0_data& data)
    {
      data.output->actual()->Bind();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

    });


    // 2st render task declaration.
    struct render_task_1_data
    {
      fbo_resource* output;
    };
    auto render_task_1 = framegraph.add_render_task<render_task_1_data>(
    "Texture Pass",
    [&] (render_task_1_data& data, fg::render_task_builder& builder)
    {
      // data.output = builder.create<fbo_resource>(fb_desc.name, fb_desc);
      data.output = builder.write<fbo_resource>(retained_resource);
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
      // fbo_resource* input;
      fbo_resource* output;
    };
    auto render_task_2 = framegraph.add_render_task<render_task_2_data>(
    "Triangle Pass",
    [&] (render_task_2_data& data, fg::render_task_builder& builder)
    {
      // data.input = builder.read<fbo_resource>(data_1.output);
      data.output = builder.write<fbo_resource>(retained_resource);
    },
    [=] (const render_task_2_data& data)
    {
      // data.input->actual()->BindColor(GL_TEXTURE1);
      data.output->actual()->Bind();
      

      triagnle_renderer->render();

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