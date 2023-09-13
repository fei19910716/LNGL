#pragma once


#include "base/utils.h"

#include "renderer.h"

/**
 * this is textured 2D quad with ibo.
*/
class TextureQuadRenderer: public Renderer
{
public:

TextureQuadRenderer()
{
    init();
}

void init() override
{
    // build and compile our shader zprogram
    // ------------------------------------
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/texture_quad/texture_quad.vs").c_str(), GL_VERTEX_SHADER);
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/texture_quad/texture_quad.fs").c_str(), GL_FRAGMENT_SHADER);
    ourShader.Link();

    // load and create a texture 
    // -------------------------
    texture2D.FromPBO(FileSystem::getPath("resources/textures/container.jpg").c_str(),false);

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

void render() override
{
    
    // bind Texture
    texture2D.Bind(GL_TEXTURE0);

    // render container
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

private:
    Shader ourShader;
    Texture2D texture2D;
    unsigned int VBO, VAO, EBO;
};