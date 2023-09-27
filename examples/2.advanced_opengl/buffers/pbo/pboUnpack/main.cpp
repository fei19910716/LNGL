#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"
#include "base/renderer/texture_quad_renderer.h"

#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
TextureQuadRenderer* renderer;

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

void init(GLFWwindow *window)
{
    ///**KEYCODE**///
    renderer = new TextureQuadRenderer; // this renderer will use pbo to load and create a texture 
    ///**KEYCODE**///

}


void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->render();
}



void clean()
{
    delete renderer;
}


ExamleMain("pboUnpack", SCR_WIDTH, SCR_HEIGHT)
