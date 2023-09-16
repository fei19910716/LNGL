#pragma once

#include <glad/glad.h>
#include <iostream>

class Texture2D
{
public:

    void FromPBO(const char* path, bool flip);
    
    void FromImage(const char* path, bool flip);

    void Bind(GLenum textureUnit);

private:
    unsigned int texture;
};