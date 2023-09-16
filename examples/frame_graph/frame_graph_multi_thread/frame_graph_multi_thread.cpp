
#include <array>
#include <cstddef>

#include "base/frame_graph/framegraph.hpp"
#include "base/renderer/texture_quad_renderer.h"
#include "base/renderer/triangle_renderer.h"
#include "base/renderer/gaussian_blur_renderer.h"
#include "base/renderer/present_renderer.h"

#include "render_thread.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


RenderThread render_thread;
ContainerQueue<Message*> message_queue;
ContainerQueue<unsigned int> texture_queue;

PresentRenderer* present_renderer;

// callbacks
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
      render_thread.stop();
    }  
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void init(GLFWwindow *window)
{
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* offscreen_context = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "", NULL, window);

    render_thread.init(offscreen_context, SCR_WIDTH, SCR_HEIGHT);
    render_thread.start(message_queue,texture_queue);
}

void run(ContainerQueue<Message*>& message_queue, ContainerQueue<unsigned int>& texture_queue)
{
  {
    // update the message, push to the queue
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));

    static int value = 1;
    Message* msg = new Message;
    msg->player_model = model;
    msg->value = value++;

    message_queue.push(msg);
  }

  {
    // pop the texture id, render the texture.
    unsigned int id = texture_queue.pop();

    if(id == GL_INVALID_VALUE) return;

    present_renderer = new PresentRenderer;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    present_renderer->render();

    glDeleteTextures(1,&id);
  }
}


void render()
{
  run(message_queue,texture_queue);
}



void clean()
{
    delete present_renderer;
}


ExamleMain("frame_graph_multi_thread", SCR_WIDTH, SCR_HEIGHT)