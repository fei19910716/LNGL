
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
Shader shader;
Texture2D texture2D;

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
    shader.LoadShaderStage("particle.vs",GL_VERTEX_SHADER);
    shader.LoadShaderStage("particle.fs",GL_FRAGMENT_SHADER);
    shader.Link();

    texture2D.FromImage(FileSystem::getPath("resources/textures/particle.png").c_str(),false);
    
    particleGenerator = new ParticleGenerator(shader, texture2D, 500);
}

double lastTime = glfwGetTime();
void render()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    lastTime = currentTime;

    GameObject go{glm::vec2(1.0f,5.0f),glm::vec2(1.0f)};
    particleGenerator->Update(delta, go, 2, glm::vec2(25.0f));


    particleGenerator->Draw();
}


void clean()
{
    delete particleGenerator;
}



ExamleMain("2.1.particles_instancing", SCR_WIDTH, SCR_HEIGHT)