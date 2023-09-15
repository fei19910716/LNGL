#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Shader
{
public:
    Shader()
    {
        ID = glCreateProgram();
    }
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

        glAttachShader(ID, vertex);

        shaders.push_back(vertex);
    }


    void Link()
    {
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


    template<typename T>
	void SetUniform(const std::string& name, const T& value)
	{
		if constexpr (std::is_same_v<T, glm::mat4>)
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
        else if constexpr (std::is_same_v<T, glm::vec4>)
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); 
        }
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
		}
        else if constexpr (std::is_same_v<T, glm::vec2>)
		{
			glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); 
		}
        else if constexpr (std::is_same_v<T, float>)
		{
			glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
		}
        else if constexpr (std::is_same_v<T, bool> || std::is_same_v<T, int>)
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
		}
	}
    
    unsigned int ID;
private:
    
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
