
/*
 * Basic Particle System realization: http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/
*/



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "particle_generator.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

ParticleGenerator* particleGenerator;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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



void init(GLFWwindow* window)
{
    particleGenerator = new ParticleGenerator;
}


void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    particleGenerator->Update(deltaTime, glm::vec2(0.0f,-0.9f));


    particleGenerator->Draw();
}


void clean()
{
    delete particleGenerator;
}



ExamleMain("2.1.particles_instancing", SCR_WIDTH, SCR_HEIGHT)