
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "base/utils.h"

#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in float inValue;\n"
    "out float geoValue;\n"
    "void main()\n"
    "{\n"
    "   geoValue = sqrt(inValue);\n"
    "}\0";

const GLchar* geoShaderSrc = "#version 330 core\n"
    "layout(points) in;\n"
    "layout(triangle_strip, max_vertices = 3) out;\n"

    "in float[] geoValue;\n"
    "out float outValue;\n"

    "void main()\n"
    "{\n"
    "    for (int i = 0; i < 3; i++) {\n"
    "        outValue = geoValue[0] + i;\n"
    "        EmitVertex();\n"
    "    }\n"

    "    EndPrimitive();\n"
    "}\n";


void framebuffer_size_callback(GLFWwindow* window, int width, int height){}
void processInput(GLFWwindow *window){}


void init(GLFWwindow* window)
{
    GLuint program = glCreateProgram();

    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &vertexShaderSource, nullptr);
    glCompileShader(shader);
    glAttachShader(program, shader);

    GLuint geoShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geoShader, 1, &geoShaderSrc, nullptr);
    glCompileShader(geoShader);
    glAttachShader(program, geoShader);

    const GLchar* feedbackVaryings[] = { "outValue" };
    glTransformFeedbackVaryings(program, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

    glLinkProgram(program);
    glUseProgram(program);


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);


    GLuint tbo;
    glGenTransformFeedbacks(1, &tbo);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tbo);

    GLuint tboBuffer;
    glGenBuffers(1, &tboBuffer);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tboBuffer);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data) * 3, nullptr, GL_STATIC_READ);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tboBuffer);
    
    glEnable(GL_RASTERIZER_DISCARD);

    glBeginTransformFeedback(GL_TRIANGLES);
    glDrawArrays(GL_POINTS, 0, 5);
    glEndTransformFeedback();

    glFlush();

    // Fetch and print results
    GLfloat feedback[15];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

    for (int i = 0; i < 15; i++) {
        printf("%f\n", feedback[i]);
    }
}

void render(){}
void clean(){}

ExamleMain("camera_circle", 800, 600)