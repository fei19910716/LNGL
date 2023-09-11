#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cstddef>

#include "base/frame_graph/framegraph.hpp"
#include "base/utils.h"



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Shader ourShader;
unsigned int VBO, VAO, EBO;



struct texture_description
{
  std::string path;
};

using texture_2d_resource = fg::resource<texture_description, Texture2D>;


namespace fg
{
template<>
std::unique_ptr<Texture2D> realize(const texture_description& description)
{
  auto ptr = std::make_unique<Texture2D>();
  ptr->FromImage(description.path.c_str(),false);
  return ptr;
}
}

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
    // build and compile our shader zprogram
    // ------------------------------------
    ourShader.LoadShaderStage("4.1.texture.vs", GL_VERTEX_SHADER);
    ourShader.LoadShaderStage("4.1.texture.fs", GL_FRAGMENT_SHADER);
    ourShader.Link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}


void render()
{
    fg::framegraph framegraph;
    // First render task declaration.
    struct render_task_1_data
    {
      texture_2d_resource* output;
    };
    auto render_task_1 = framegraph.add_render_task<render_task_1_data>(
    "Render Task 1",
    [&] (render_task_1_data& data, fg::render_task_builder& builder)
    {
      texture_description td;
      td.path = FileSystem::getPath("resources/textures/container.jpg");
      data.output = builder.create<texture_2d_resource>("Resource 1", td);
    },
    [=] (const render_task_1_data& data)
    {
      // Perform actual rendering. You may load resources from CPU by capturing them.
      auto actual = data.output->actual();

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // bind Texture
      actual->Bind(GL_TEXTURE0);

      // render container
      ourShader.use();
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });
      framegraph.compile();
      framegraph.execute();
      framegraph.clear();
}



void clean()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


ExamleMain("hello_triangle_frame_graph", SCR_WIDTH, SCR_HEIGHT)