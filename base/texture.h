#pragma once

#include <glad/glad.h>
#include <iostream>

class Texture2D
{
public:

    void FromPBO(const char* path, bool flip);
    
    void FromImage(const char* path, bool flip);

    void Bind(GLenum textureUnit);

    unsigned int ID() const
    {
        return texture;
    }
private:
    unsigned int texture;
};