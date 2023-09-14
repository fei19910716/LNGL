#pragma once

#include "base/utils.h"

class RandomTexture
{
public:
    RandomTexture();

    ~RandomTexture();
    
    bool InitRandomTexture(unsigned int Size);

    void Bind(GLenum TextureUnit);

private:
    GLuint m_textureObj;
};



RandomTexture::RandomTexture()
{
    m_textureObj = 0;    
}


RandomTexture::~RandomTexture()
{
    if (m_textureObj != 0) {
        glDeleteTextures(1, &m_textureObj);
    }
}

/**
 * return [0.0f,1.0f]
*/
float RandomFloat()
{
    /**
     * rand(): Returns a pseudo-random integer value between ​0​ and RAND_MAX (0 and RAND_MAX included).
    */
    float Max = RAND_MAX;
    return ((float)rand() / Max);
}


bool RandomTexture::InitRandomTexture(unsigned int Size)
{
    glm::vec3* pRandomData = new glm::vec3[Size];
    for (unsigned int i = 0 ; i < Size ; i++) {
        pRandomData[i].x = RandomFloat();
        pRandomData[i].y = RandomFloat();
        pRandomData[i].z = RandomFloat();
    }
        
    glGenTextures(1, &m_textureObj);
    glBindTexture(GL_TEXTURE_1D, m_textureObj);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, Size, 0, GL_RGB, GL_FLOAT, pRandomData);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
    
    delete [] pRandomData;
    
    return true;
}

    
void RandomTexture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_1D, m_textureObj);
}