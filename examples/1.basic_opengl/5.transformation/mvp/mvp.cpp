#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Shader ourShader;
Texture2D texture2D_1, texture2D_2;
unsigned int VBO, VAO, EBO;

// callbacks
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow *window)
{
    // build and compile our shader zprogram
    // ------------------------------------
    ourShader.LoadShaderStage("6.1.coordinate_systems.vs", GL_VERTEX_SHADER);
    ourShader.LoadShaderStage("6.1.coordinate_systems.fs", GL_FRAGMENT_SHADER);
    ourShader.Link();

    // load and create a texture 
    // -------------------------
    texture2D_1.FromImage(FileSystem::getPath("resources/textures/container.jpg").c_str(),false);
    texture2D_2.FromImage(FileSystem::getPath("resources/textures/awesomeface.png").c_str(),false);

    // the quad is along the z=0 plane
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    ourShader.use();
    ourShader.SetUniform<int>("texture1", 0);
    ourShader.SetUniform<int>("texture2", 1);
}


void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    texture2D_1.Bind(GL_TEXTURE0);
    texture2D_2.Bind(GL_TEXTURE1);

    ourShader.use();
    

    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    // rotate the quad along the x axis
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // put camera at (3.0f, 0.0f, 0.0f) and look at -Z by default;
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    // set the camera frustrum parameter
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    
    ourShader.SetUniform<glm::mat4>("model",model);
    ourShader.SetUniform<glm::mat4>("view",view);
    ourShader.SetUniform<glm::mat4>("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void clean()
{

}

ExamleMain("6.1.coordinate_systems", SCR_WIDTH, SCR_HEIGHT)