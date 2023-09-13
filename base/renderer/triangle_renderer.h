#pragma once


#include "base/utils.h"

#include "renderer.h"

/**
 * this is colored triangle without texture, without ibo.
*/
class TriangleRenderer: public Renderer
{
public:

TriangleRenderer()
{
    init();
}

void init() override
{
    // build and compile our shader zprogram
    // ------------------------------------
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/triangle/triangle.vs").c_str(), GL_VERTEX_SHADER);
    ourShader.LoadShaderStage(FileSystem::getPath("resources/shaders/triangle/triangle.fs").c_str(), GL_FRAGMENT_SHADER);
    ourShader.Link();


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

template<typename T>
void SetUniform(const std::string& name, const T& value)
{
    ourShader.use();
    ourShader.SetUniform<T>(name,value);
}

void render() override
{
    // render the triangle
    ourShader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

private:
    Shader ourShader;
    unsigned int VBO, VAO, EBO;
};