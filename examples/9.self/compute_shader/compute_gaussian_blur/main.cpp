#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"
#include "base/renderer/present_renderer.h"
#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
PresentRenderer* presentRenderer;
unsigned int output_texture;

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
    int width, height, nrChannels;
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);

    // create the input texture
    unsigned int input_texture;
    glGenTextures(1, &input_texture);
    glBindTexture(GL_TEXTURE_2D, input_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F/*this must be GL_RGBA32F*/, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // create the output texture
    glGenTextures(1, &output_texture);
    glBindTexture(GL_TEXTURE_2D, output_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F/*this must be GL_RGBA32F*/, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // dispatch
    Shader computeShader;
	computeShader.LoadShaderStage("compute_gaussian_blur.cs",GL_COMPUTE_SHADER);
	computeShader.Link();
    computeShader.use();
    glBindImageTexture(0, input_texture, 0,  GL_FALSE, 0,  GL_READ_ONLY, GL_RGBA32F);
    glBindImageTexture(1, output_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute((unsigned int)width/16, (unsigned int)height/16, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // render with the output texture
    presentRenderer = new PresentRenderer;
}

void render()
{
    presentRenderer->BindTexture(GL_TEXTURE0, output_texture);
    presentRenderer->render();
}

void clean(){}


ExamleMain("compute_gaussian_blur", SCR_WIDTH, SCR_HEIGHT)