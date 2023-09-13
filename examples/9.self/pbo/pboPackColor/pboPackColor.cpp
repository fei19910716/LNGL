#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"
#include "base/renderer/triangle_renderer.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

TriangleRenderer* renderer;
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
    renderer = new TriangleRenderer;


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
    renderer->render();

    ///**KEYCODE**///
    static int index = 0;
    index = (index + 1) % 2;
    int nextIndex = (index + 1) % 2;

    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
    glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    // glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
    GLubyte* src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    if(src)
    {
        // change brightness
        stbi_write_png("pboPackColor.png",SCR_WIDTH,SCR_HEIGHT,4,src,0);
        glUnmapBuffer(GL_PIXEL_PACK_BUFFER);        // release pointer to the mapped buffer
    }
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    ///**KEYCODE**///
}

void clean()
{
    delete renderer;
}

ExamleMain("pboPackColor", SCR_WIDTH, SCR_HEIGHT)