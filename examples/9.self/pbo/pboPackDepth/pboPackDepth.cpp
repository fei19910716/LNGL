#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "base/utils.h"
#include "base/renderer/texture_cube_renderer.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
TextureCubeRenderer* renderer;
unsigned int pboIds[2];

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
    renderer = new TextureCubeRenderer;

    ///**KEYCODE**///
    glGenBuffers(2, pboIds);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, SCR_WIDTH * SCR_HEIGHT * 4, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, SCR_WIDTH * SCR_HEIGHT * 4, 0, GL_STREAM_READ);
    ///**KEYCODE**///
}


void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render();

    ///**KEYCODE**///
    static int index = 0;
    index = (index + 1) % 2;
    int nextIndex = (index + 1) % 2;

    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
    glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
    GLubyte* src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    if(src)
    {
        // change brightness
        stbi_write_png("pboPackDepth.png",SCR_WIDTH,SCR_HEIGHT,4,src,0);
        glUnmapBuffer(GL_PIXEL_PACK_BUFFER);        // release pointer to the mapped buffer
    }
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    ///**KEYCODE**///
}



void clean()
{
    delete renderer;
}

ExamleMain("6.2.coordinate_systems_depth", SCR_WIDTH, SCR_HEIGHT)