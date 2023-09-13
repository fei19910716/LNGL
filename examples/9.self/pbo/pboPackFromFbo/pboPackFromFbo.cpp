#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"
#include "base/renderer/triangle_renderer.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

TriangleRenderer* renderer;
FrameBuffer* fbo;
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

    FrameBuffer::Description desc;
    {
        desc.width = SCR_WIDTH;
        desc.height = SCR_HEIGHT;
        desc.color_format = GL_RGBA;
        desc.depth_format = GL_DEPTH24_STENCIL8;
    }

    fbo = new FrameBuffer(desc);


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
    fbo->Bind();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->render();

    // use Blit instead of a present renderer
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->ID());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT,
                      0, 0, SCR_WIDTH, SCR_HEIGHT,
                      GL_COLOR_BUFFER_BIT,
                      GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    ///**KEYCODE**///
    static int index = 0;
    index = (index + 1) % 2;
    int nextIndex = (index + 1) % 2;

    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo->ID());
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[index]);
    glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[nextIndex]);
    GLubyte* src = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    if(src)
    {
        // change brightness
        stbi_write_png("pboPackFromFbo.png",SCR_WIDTH,SCR_HEIGHT,4,src,0);
        glUnmapBuffer(GL_PIXEL_PACK_BUFFER);        // release pointer to the mapped buffer
    }
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    ///**KEYCODE**///
}

void clean()
{
    delete renderer;
}

ExamleMain("pboPackFromFbo", SCR_WIDTH, SCR_HEIGHT)