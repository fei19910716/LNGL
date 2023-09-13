#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include "frame_graph/resource.hpp"

class FrameBuffer{
public:

    struct Description
    {
        unsigned int width, height;
        GLenum color_format, depth_format;
        std::string name;

        unsigned int fbo_id = GL_INVALID_INDEX, color_id = GL_INVALID_INDEX, depth_id = GL_INVALID_INDEX;
    };

    FrameBuffer() = default;
    FrameBuffer(const Description& fbo_desc)
    {
        // framebuffer configuration
        // -------------------------
        if(fbo_desc.fbo_id != GL_INVALID_INDEX)
        {
            framebuffer = fbo_desc.fbo_id;
        }else{
            glGenFramebuffers(1, &framebuffer);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        // create a color attachment texture
        if(fbo_desc.color_id != GL_INVALID_INDEX)
        {
            color = fbo_desc.color_id;
            glBindTexture(GL_TEXTURE_2D, color);
        }else{
            glGenTextures(1, &color);
            glBindTexture(GL_TEXTURE_2D, color);
            glTexImage2D(GL_TEXTURE_2D, 0, fbo_desc.color_format, fbo_desc.width, fbo_desc.height, 0, fbo_desc.color_format, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);
        
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        if(fbo_desc.depth_id != GL_INVALID_INDEX)
        {
            depth = fbo_desc.depth_id;
            glBindRenderbuffer(GL_RENDERBUFFER, depth);
        }else{
            glGenRenderbuffers(1, &depth);
            glBindRenderbuffer(GL_RENDERBUFFER, depth);
            glRenderbufferStorage(GL_RENDERBUFFER, fbo_desc.depth_format, fbo_desc.width, fbo_desc.height); // use a single renderbuffer object for both a depth AND stencil buffer.
        }
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth); // now actually attach it
        
        
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }

    void BindColor(GLenum textureUnit)
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, color);
    }

    unsigned int ID() const
    {
        return framebuffer;
    }

private:
    std::string name;
    unsigned int framebuffer = 0, color, depth;

};

using fbo_resource = fg::resource<FrameBuffer::Description, FrameBuffer>;

namespace fg
{
template<>
std::unique_ptr<FrameBuffer> realize(const FrameBuffer::Description& description)
{
  return std::make_unique<FrameBuffer>(description);
}
}