#pragma once


#include "base/utils.h"

#include "renderer.h"

class GuassianBlurRenderer: public Renderer
{
public:

GuassianBlurRenderer()
{
    init();
}

void init() override
{
    // build and compile our shader zprogram
    // ------------------------------------
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/gaussian_blur/gaussian_blur.vs").c_str(), GL_VERTEX_SHADER);
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/gaussian_blur/gaussian_blur.fs").c_str(), GL_FRAGMENT_SHADER);
    ourShader.Link();

    float quadVertices[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    // setup plane VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void BindTexture(GLenum textureUnit, unsigned int id)
{
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void render() override
{
    // render container
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

private:
    Shader ourShader;
    Texture2D texture2D;
    unsigned int VBO, VAO, EBO;
};