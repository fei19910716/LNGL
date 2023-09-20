#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void init(GLFWwindow *window)
{
    // load a texture

    // create the output texture

    // dispatch

    // render with the output texture
}

void render()
{

}

void clean(){}


ExamleMain("compute_gaussian_blur", SCR_WIDTH, SCR_HEIGHT)