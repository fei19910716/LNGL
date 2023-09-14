#pragma once

#include <string>

#include "base/utils.h"

#define NUM 2

class BillboardRenderer
{
public:
    BillboardRenderer()
    {
        Init();
    } 
    ~BillboardRenderer()
    {
        glDeleteBuffers(1, &VBO);
    }
    
    bool Init();
    
    void Render(const glm::mat4& VP, const glm::vec3& CameraPos);

private:
    
    GLuint VAO,VBO;
    Texture2D m_texture;
    Shader shader;
};

    

bool BillboardRenderer::Init()
{
    m_texture.FromImage(FileSystem::getPath("resources/textures/awesomeface.png").c_str(),false);
        
    shader.LoadShaderStage("billboad.vs",GL_VERTEX_SHADER);
    shader.LoadShaderStage("billboad.gs",GL_GEOMETRY_SHADER);
    shader.LoadShaderStage("billboad.fs",GL_FRAGMENT_SHADER);
    shader.Link();

    glm::vec3 Positions[NUM];
    Positions[0] = glm::vec3(-0.5f,0.0f,0.5f);
    Positions[1] = glm::vec3( 0.5f,0.0f,-0.5f);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
  	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions), &Positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);   // position
    glBindVertexArray(0);
    
    return true;
}


void BillboardRenderer::Render(const glm::mat4& VP, const glm::vec3& CameraPos)
{
    shader.use();
    shader.SetUniform<glm::mat4>("gVP",VP);
    shader.SetUniform<glm::vec3>("gCameraPos",CameraPos);
    
    m_texture.Bind(GL_TEXTURE0);
    
    glBindVertexArray(VAO);

    glDrawArrays(GL_POINTS, 0, NUM);
    
}