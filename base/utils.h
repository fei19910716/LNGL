#pragma once

#include "shader_cf.h"
#include "texture.h"
#include "fbo.h"

#define ExamleMain(name,width,height)                                               \
int main()                                                                          \
{                                                                                   \
glfwInit();                                                                         \
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                                      \
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                                      \
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                      \
                                                                                    \
GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);             \
if (window == NULL)                                                                 \
{                                                                                   \
    std::cout << "Failed to create GLFW window" << std::endl;                       \
    glfwTerminate();                                                                \
    return -1;                                                                      \
}                                                                                   \
                                                                                    \
glfwMakeContextCurrent(window);                                                     \
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);                  \
                                                                                    \
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                            \
                                                                                    \
{                                                                                   \
    std::cout << "Failed to initialize GLAD" << std::endl;                          \
    return -1;                                                                      \
}                                                                                   \
                                                                                    \
init();                                                                             \
                                                                                    \
do                                                                                  \
{                                                                                   \
    processInput(window);                                                           \
                                                                                    \
    render();                                                                       \
                                                                                    \
    glfwSwapBuffers(window);                                                        \
    glfwPollEvents();                                                               \
                                                                                    \
}while (!glfwWindowShouldClose(window));                                            \
                                                                                    \
glfwTerminate();                                                                    \
                                                                                    \
clean();                                                                            \
                                                                                    \
return 0;                                                                           \
}                                                                                   \