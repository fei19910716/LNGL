
#pragma once

#include <vector>
#include <random>

#include <glad/glad.h>
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
};

#define TOTAL 2000
#define NEW   2

/**
 * ParticleGenerator acts as a container for rendering a large number of 
 * particles by repeatedly spawning and updating particles and killing 
 * them after a given amount of time.
*/
class ParticleGenerator
{
public:
    ParticleGenerator()
    {
        this->init();
    }

    // update all particles
    void Update(float dt, glm::vec2 location)
    {
        // add new particles 
        for (unsigned int i = 0; i < NEW; ++i)
        {
            int unusedParticle = this->firstUnusedParticle();
            this->respawnParticle(this->particles[unusedParticle], location);
        }
        // update all particles
        for (unsigned int i = 0; i < TOTAL; ++i)
        {
            Particle &particle = this->particles[i];
            particle.Life -= dt * 0.5f; // reduce life
            if (particle.Life > 0.0f)
            {	
                // particle is alive, thus update
                particle.Position += particle.Velocity * dt * 0.5f; 
                particle.Color.a  -= dt * 2.5f;
            }
        }
    }


    // render all particles
    void Draw()
    {
        // use additive blending to give it a 'glow' effect
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        this->shader.use();
        for (Particle particle : this->particles)
        {
            if (particle.Life > 0.0f)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model,glm::vec3(particle.Position,0.0f));
                model = glm::scale(model,glm::vec3(0.03f));
                this->shader.SetUniform<glm::mat4>("model", model);
                this->shader.SetUniform<glm::vec4>("color", particle.Color);
                this->texture.Bind(GL_TEXTURE0);
                glBindVertexArray(this->VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
        // don't forget to reset to default blending mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    // initializes buffer and vertex attributes
    void init()
    {
        shader.LoadShaderStage("particle.vs",GL_VERTEX_SHADER);
        shader.LoadShaderStage("particle.fs",GL_FRAGMENT_SHADER);
        shader.Link();

        texture.FromImage(FileSystem::getPath("resources/textures/awesomeface.png").c_str(),false);

        // set up mesh and attribute properties
        unsigned int VBO;
        float particle_quad[] = {
            // position // texCoords
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        }; 
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(this->VAO);
        // fill mesh buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
        // set mesh attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindVertexArray(0);

        // create this->amount default particle instances
        for (unsigned int i = 0; i < TOTAL; ++i)
            this->particles.push_back(Particle());
    }


    // returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    unsigned int firstUnusedParticle();


    /**
     * re-alive the dead particle
    */
    void respawnParticle(Particle &particle, glm::vec2 location)
    {
        std::random_device rd;
        std::default_random_engine generator(rd());

        particle.Position = location;
        particle.Color = glm::vec4(1.0f);
        particle.Life = 1.0f;

        // inject particle up by default
        std::uniform_real_distribution<double> distribution_vel(-0.2, 0.2);
        particle.Velocity = glm::vec2(0.0f,1.0f) + glm::vec2(distribution_vel(generator),distribution_vel(generator));
    }


private:
    // state
    std::vector<Particle> particles;
    unsigned int lastAliveParticle = 0;

    // render state
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
};

// stores the index of the last particle used (for quick access to next dead particle)
unsigned int ParticleGenerator::firstUnusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastAliveParticle; i < TOTAL; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastAliveParticle = i;
            return lastAliveParticle;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastAliveParticle; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastAliveParticle = i;
            return lastAliveParticle;
        }
    }

    // all particles are alive, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastAliveParticle = 0;
    return lastAliveParticle;
}