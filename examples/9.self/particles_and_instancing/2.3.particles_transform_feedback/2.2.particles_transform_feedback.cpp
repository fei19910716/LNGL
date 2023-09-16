

/*
 * Particle System using Transform Feedback: https://ogldev.org/www/tutorial28/tutorial28.html
*/


/**
 * use geometry shaders to implement billboarding.
 * 
 * Billboards are often used to create a forest where a large number of trees is required in order to create the effect.
 * 
 * 1, input the camera and billboard point
 * 2, create a vector from the billboard location to the camera
 * 3, add the vector (0,1,0)
 * 4, do a cross product between these two vectors. This vector points in the exact direction along which we need to extend the point and create a quad.
 * 5, we get the quad always face to the camera, which is a billboad.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <base/utils.h>
#include "particle_system_tf.h"

#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
CParticleSystemTransformFeedback psMainParticleSystem;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
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


    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


void init(GLFWwindow *window)
{
    psMainParticleSystem.InitalizeParticleSystem();
    psMainParticleSystem.SetGeneratorProperties(
		glm::vec3(0.0f, -0.9f, 0.0f), // Where the particles are generated
		glm::vec3(-0.3f, 0.0f, 0.0f), // Minimal velocity
		glm::vec3(0.3f, 2.0f, 0.0f), // Maximal velocity
		glm::vec3(0.0f,-1.0f, 0.0f), // Gravity force applied to particles
		glm::vec3(0.0f, 0.5f, 1.0f), // Color (light blue)
		1.5f, // Minimum lifetime in seconds
		5.0f, // Maximum lifetime in seconds
		0.03f, // Rendered size
		0.5f, // Spawn every 0.05 seconds
		100); // And spawn 30 particles
}


void render()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);

    // camera/view transformation
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    psMainParticleSystem.SetMatrices(&projection, cameraPos, cameraPos + cameraFront, cameraUp);

	psMainParticleSystem.UpdateParticles(deltaTime);
	psMainParticleSystem.RenderParticles();
}


void clean()
{

}



ExamleMain("2.3.particles_transform_feedback", SCR_WIDTH, SCR_HEIGHT)