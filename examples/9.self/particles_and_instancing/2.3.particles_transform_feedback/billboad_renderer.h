#pragma once

#include <string>

#include "base/utils.h"


/**
 * Particle has a Life, which will update per frame
 * Particle has a velocity to movement.
 * 
 * when life < 0, which means this particle dead.
*/
struct Particle {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }

    void toString()
    {
        std::cout << "Position: (" << Position.x << "," << Position.y << ")" << ", "
                  << "Velocity: (" << Velocity.x << "," << Velocity.y << ")" << ", "
                  << "Color: (" << Color.x << "," << Color.y << "," << Color.z << "," << Color.w << ")" << ", "
                  << "Life: " << Life << std::endl;

    }
};


class BillboardRenderer
{
public:
    BillboardRenderer(const std::vector<Particle>& particles)
    {
        count = particles.size();
        Init(particles);
    } 
    ~BillboardRenderer()
    {
        glDeleteBuffers(1, &VBO);
    }
    
    bool Init(const std::vector<Particle>& particles);
    
    void Render(const glm::mat4& VP, const glm::vec3& CameraPos);

private:
    GLuint VAO,VBO;
    Texture2D m_texture;
    Shader shader;

    size_t count;
};

    

bool BillboardRenderer::Init(const std::vector<Particle>& particles)
{
    m_texture.FromImage(FileSystem::getPath("resources/textures/awesomeface.png").c_str(),false);
        
    shader.LoadShaderStage("billboad.vs",GL_VERTEX_SHADER);
    shader.LoadShaderStage("billboad.gs",GL_GEOMETRY_SHADER);
    shader.LoadShaderStage("billboad.fs",GL_FRAGMENT_SHADER);
    shader.Link();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
  	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), particles.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Life));

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

    glDrawArrays(GL_POINTS, 0, (GLsizei)count);
    
}