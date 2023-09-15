
#pragma once

#include "billboad_renderer.h"
#include "random_texture.h"

#define MAX_PARTICLES 100
#define PARTICLE_LIFETIME 10.0f
#define NEW_PARTICLES   2


class ParticleSystem
{
public:
    ParticleSystem(const glm::vec3& Pos);
    
    ~ParticleSystem();
    
    void Update(float dt);
    
    void Render(const glm::mat4& VP, const glm::vec3& CameraPos);
    
private:
    void UpdateParticles(float dt);
    void RenderParticles(const glm::mat4& VP, const glm::vec3& CameraPos);
    
    BillboardRenderer* renderer;

    Shader particleShader;
    RandomTexture randomTexture;
    unsigned int tbo, tboBuffer;

    Texture2D billboadTexture;
    Shader billboadShader;

    bool firstTime = true;
};



ParticleSystem::ParticleSystem(const glm::vec3& Pos)
{
    {
        particleShader.LoadShaderStage("tfo.vs",GL_VERTEX_SHADER);
        particleShader.LoadShaderStage("tfo.gs",GL_GEOMETRY_SHADER);
        particleShader.LoadShaderStage("tfo.fs",GL_FRAGMENT_SHADER);

        const GLchar* feedbackVaryings[] = { "outPosition","outVelocity","outColor","outLife"};
        glTransformFeedbackVaryings(particleShader.ID, 4, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
        particleShader.Link();

        Particle data;
        data.Position = glm::vec2(0.0f,-0.9f); data.Life = 1.0f; data.Velocity = glm::vec2(0.0f,1.0f);

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Life));


        glGenTransformFeedbacks(1, &tbo);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tbo);

        glGenBuffers(1, &tboBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, tboBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * MAX_PARTICLES, nullptr, GL_STATIC_READ);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tboBuffer);
    }

    {   // render the first time to initialize tboBuffer.
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tbo);
            glEnable(GL_RASTERIZER_DISCARD);

            particleShader.use();
            randomTexture.Bind(GL_TEXTURE0);
            glBeginTransformFeedback(GL_POINTS);
            glDrawArrays(GL_POINTS, 0, 1);
            glEndTransformFeedback();

            glFlush();

            glDisable(GL_RASTERIZER_DISCARD);

            // // Fetch and print results
            // std::vector<Particle> feedback(MAX_PARTICLES);
            // glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(Particle) * MAX_PARTICLES, feedback.data());

            // for(int i = 0; i < 3; i++){
            //     feedback[i].toString();
            // }
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

        // renderer = new BillboardRenderer(feedback);
    }

    {
        billboadTexture.FromImage(FileSystem::getPath("resources/textures/awesomeface.png").c_str(),false);
        
        billboadShader.LoadShaderStage("billboad.vs",GL_VERTEX_SHADER);
        billboadShader.LoadShaderStage("billboad.gs",GL_GEOMETRY_SHADER);
        billboadShader.LoadShaderStage("billboad.fs",GL_FRAGMENT_SHADER);
        billboadShader.Link();

        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tboBuffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Color));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle,Life));
    }
}


ParticleSystem::~ParticleSystem()
{
    // delete renderer;
}

void ParticleSystem::Update(float dt)
{
    UpdateParticles(dt);
}


void ParticleSystem::Render(const glm::mat4& VP, const glm::vec3& CameraPos)
{
    RenderParticles(VP, CameraPos);
}


void ParticleSystem::UpdateParticles(float dt)
{
    if(false == firstTime)
    {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tbo);
            glEnable(GL_RASTERIZER_DISCARD);

            particleShader.use();
            glBeginTransformFeedback(GL_POINTS);
            glDrawTransformFeedback(GL_POINTS, tbo);
            glEndTransformFeedback();

            glFlush();

            glDisable(GL_RASTERIZER_DISCARD);

            // Fetch and print results
            std::vector<Particle> feedback(MAX_PARTICLES);
            glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(Particle) * MAX_PARTICLES, feedback.data());

            for(int i =0; i < 3; i++){
                // feedback[i].toString();
            }
            // std::cout << "------------------------" << std::endl;
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
        
    }
}
    

void ParticleSystem::RenderParticles(const glm::mat4& VP, const glm::vec3& CameraPos)
{
    {
        billboadShader.use();
        billboadShader.SetUniform<glm::mat4>("gVP",VP);
        billboadShader.SetUniform<glm::vec3>("gCameraPos",CameraPos);
        
        billboadTexture.Bind(GL_TEXTURE0);
        
        glBindBuffer(GL_ARRAY_BUFFER, tboBuffer);   

        glDrawTransformFeedback(GL_POINTS, tbo);
    }
    // renderer->Render(VP,CameraPos);

    firstTime = false;
}