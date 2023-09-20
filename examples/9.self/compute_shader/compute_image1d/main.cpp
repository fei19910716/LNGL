
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "base/utils.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLuint programId, computeShaderId;
GLuint inputTexId, outputTexId;

const int kArraySize = 32;

const GLchar* Program = " \
    #version 430\n\
    layout (local_size_x = 16, local_size_y = 1) in;\n\
    layout (r32f, binding = 0) uniform image1D in_array; \n\
    layout (r32f, binding = 1) uniform image1D out_array; \n\
    \
    void main() \n\
    { \
        int pos = int(gl_GlobalInvocationID.x);\n\
        vec4 value = imageLoad(in_array, pos);\n\
        value.x += 1.0f;\n\
        imageStore(out_array, pos, value);\n\
    } \
";


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

void CheckGLErrors() 
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error: (%d)\n", e);
        exit(20);
    }
}

void CreateShaders(void)
{
    GLchar messages[256];
    GLenum ErrorCheckValue = glGetError();

    /* Compile the shader. */
    computeShaderId = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShaderId, 1, &Program, NULL);
    glCompileShader(computeShaderId);

    /* Print the compilation log. */
    glGetShaderInfoLog(computeShaderId, sizeof(messages), NULL, messages);

    /* Set up program objects. */
    programId = glCreateProgram();

    /* Create a complete program object. */
    glAttachShader(programId, computeShaderId);
    glLinkProgram(programId);

    /* And print the link log. */
    glGetProgramInfoLog(programId, sizeof(messages), NULL, messages);

    CheckGLErrors();
}

void CreateTexture(void)
{
    // Create the input texture
    glGenTextures(1, &inputTexId);

    // And bind it to texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, inputTexId);
    // Set texture size and format
    glTexStorage1D(GL_TEXTURE_1D, 1, GL_R32F, kArraySize);

    CheckGLErrors();

    // Create the output texture
    glGenTextures(1, &outputTexId);

    // And bind it to texture unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_1D, outputTexId);
    // Set texture size and format
    glTexStorage1D(GL_TEXTURE_1D, 1, GL_R32F, kArraySize);

    glBindImageTexture(0, inputTexId, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R32F);
    glBindImageTexture(1, outputTexId, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

    CheckGLErrors();
}


void DoCompute()
{
    float *inputData = new float[kArraySize];
    float *outputData = new float[kArraySize];

    for (int i = 0; i < kArraySize; i++)
    {
        inputData[i] = (float)i;
    }

    glBindTexture(GL_TEXTURE_1D, inputTexId);
    glTexSubImage1D(GL_TEXTURE_1D, 0, 0, kArraySize, GL_RED, GL_FLOAT, inputData);


    { // launch compute shaders!
        glUseProgram(programId);
        glDispatchCompute((GLuint)kArraySize/16, 1, 1);
    }

    // make sure writing to image has finished before read
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    glBindTexture(GL_TEXTURE_1D, outputTexId);
    glGetTexImage(GL_TEXTURE_1D, 0, GL_RED, GL_FLOAT, outputData);
    glBindTexture(GL_TEXTURE_2D, 0);

    CheckGLErrors();

    for (int i = 0; i < 5; i++)
    {
        printf("%f ", outputData[i]);
    }

    delete []outputData;
    delete []inputData;
}

void init(GLFWwindow* window)
{
    CreateShaders();
    CreateTexture();

    DoCompute();
}

void render(){}

void clean()
{

}

ExamleMain("compute_image1d", SCR_WIDTH, SCR_HEIGHT)