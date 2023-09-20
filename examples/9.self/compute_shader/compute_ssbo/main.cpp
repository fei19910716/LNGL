#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "base/utils.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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

void init(GLFWwindow *window)
{
    float ssbo_data[4] = {0.0f, 1.0f, 2.0f, 3.0f};

    GLuint in_ssbo = 0;
    glGenBuffers(1, &in_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, in_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ssbo_data), NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    GLuint out_ssbo = 0;
    glGenBuffers(1, &out_ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, out_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ssbo_data), NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, in_ssbo);
        // GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        // memcpy(p, &ssbo_data, sizeof(ssbo_data));
        // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

        glBufferSubData(GL_SHADER_STORAGE_BUFFER,0,sizeof(ssbo_data),ssbo_data);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }



    Shader computeShader;
    computeShader.LoadShaderStage("compute_ssbo.cs",GL_COMPUTE_SHADER);
    computeShader.Link();

    // this is done in the glsl.
    // glShaderStorageBlockBinding(computeShader.ID, glGetProgramResourceIndex(computeShader.ID, GL_SHADER_STORAGE_BLOCK, "Result"), 0);
    // glShaderStorageBlockBinding(computeShader.ID, glGetProgramResourceIndex(computeShader.ID, GL_SHADER_STORAGE_BLOCK, "In_p1"),  1);
    

    computeShader.use();
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, out_ssbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, in_ssbo);
    
    glDispatchCompute(2, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, out_ssbo);
    GLfloat *ptr = (GLfloat *) glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
    for(int i = 0; i < 4; i++)
    {
        std::cout << ptr[i] << ",";
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void render(){}
void clean(){}

ExamleMain("compute_ssbo", SCR_WIDTH, SCR_HEIGHT)