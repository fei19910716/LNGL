#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Shader
{
public:
    Shader() = default;
    ~Shader()
    {
        glDeleteProgram(ID);
    }
    
    void LoadShaderStage(const char* path, GLenum stage)
    {
        std::string vertexCode;
        std::ifstream vShaderFile;

        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(path);

            std::stringstream vShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();

            // convert stream into string
            vertexCode   = vShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();

        unsigned int vertex;
        // vertex shader
        vertex = glCreateShader(stage);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex);

        shaders.push_back(vertex);
    }


    void Link()
    {
        // shader Program
        ID = glCreateProgram();

        for(auto shader: shaders)
        {
            glAttachShader(ID, shader);
        }
        
        glLinkProgram(ID);
        checkLinkErrors(ID);

        // delete the shaders as they're linked into our program now and no longer necessary
        for(auto shader: shaders)
        {
            glDeleteShader(shader);
        }
    }

    
    // activate the shader
    // ------------------------------------------------------------------------
    void use() 
    { 
        glUseProgram(ID); 
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

private:
    unsigned int ID;
    std::vector<unsigned int> shaders;
    
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader)
    {
        int success;
        char infoLog[1024];
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void checkLinkErrors(unsigned int program)
    {
        int success;
        char infoLog[1024];
        {
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(program, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif
