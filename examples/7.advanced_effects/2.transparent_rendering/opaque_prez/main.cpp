#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

#include <iostream>
#include <map>
#include <vector>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Shader shader, preZshader;
Texture2D cubeTexture,floorTexture;
unsigned int cubeVAO, cubeVBO;
unsigned int planeVAO, planeVBO;
unsigned int framebuffer;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// callbacks
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow *window)
{
    // build and compile shaders
    // -------------------------
    shader.LoadShaderStage("opaque_prez.vs", GL_VERTEX_SHADER);
    shader.LoadShaderStage("opaque_prez.fs", GL_FRAGMENT_SHADER);
    shader.Link();
    preZshader.LoadShaderStage("opaque_prez.vs", GL_VERTEX_SHADER);
    preZshader.LoadShaderStage("depth_prez.fs", GL_FRAGMENT_SHADER);
    preZshader.Link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f								
    };
    // cube VAO
    
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    // plane VAO
    
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    cubeTexture.FromImage(FileSystem::getPath("resources/textures/marble.jpg").c_str(),false);
    floorTexture.FromImage(FileSystem::getPath("resources/textures/metal.png").c_str(),false);
}


void render()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(-5.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shader.SetUniform("view", view);
    preZshader.SetUniform("view", view);
    shader.SetUniform("projection", projection);
    preZshader.SetUniform("projection", projection);
       
    std::vector<glm::vec3> cubes
    {
        glm::vec3(-1.0f, 0.0f, -1.0f),
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(-2.0f, 0.0f, 1.2f),
        glm::vec3(-2.0f, 0.0f, 2.4f),
        glm::vec3(-2.0f, 0.0f, 3.6f)
    };

    /**
     * Pre-Z pass, use a simple fragment shader
    */
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
    glBindVertexArray(cubeVAO); cubeTexture.Bind(GL_TEXTURE0);
    for (auto& cube: cubes)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cube);
        preZshader.SetUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // floor
    glBindVertexArray(planeVAO);floorTexture.Bind(GL_TEXTURE0);
    preZshader.SetUniform("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    /**
     * Draw pass
    */
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glEnable(GL_DEPTH_TEST);glDepthFunc(GL_EQUAL);
    glBindVertexArray(cubeVAO);cubeTexture.Bind(GL_TEXTURE0);
    for (auto& cube: cubes)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cube);
        shader.SetUniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // floor
    glBindVertexArray(planeVAO);floorTexture.Bind(GL_TEXTURE0);
    shader.SetUniform("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void clean()
{

}


ExamleMain("transparent_rendering_opaque_prez", SCR_WIDTH, SCR_HEIGHT)