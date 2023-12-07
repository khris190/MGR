#include "VBO.hpp"
#include "my_utils/Profiler.hpp"
#include <iostream>
#include <vector>

VBO::VBO(uint width, uint height)
{
    this->width = width;
    this->height = height;
    if (INT32_MAX < this->getWidth() * this->getHeight() * 4) {
        std::cerr << "IMG INT OVERFLOWW BY: " << this->getWidth() * this->getHeight() * 4 - INT32_MAX << " BYTES" << std::endl;
        exit(10);
    }
    // Create FBO
    glGenFramebuffers(1, &this->vboId);
    glBindFramebuffer(GL_FRAMEBUFFER, this->vboId);

    // Create Multisampled Texture
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->textureId);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, width, height, GL_TRUE); // 4 samples per pixel
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->textureId, 0);

    // Check framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Framebuffer is not complete!" << std::endl;
    }
    glGenFramebuffers(1, &this->resolveVboId);
    glBindFramebuffer(GL_FRAMEBUFFER, this->resolveVboId);
    glGenTextures(1, &this->resolveTextureId);
    glBindTexture(GL_TEXTURE_2D, this->resolveTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->resolveTextureId, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "error framebuffer";
    }
}
VBO::~VBO()
{
    glDeleteTextures(1, &this->textureId);
    glDeleteFramebuffers(1, &this->vboId);
    glDeleteFramebuffers(1, &this->resolveVboId);
    glDeleteTextures(1, &this->resolveTextureId);
}

void VBO::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->vboId);
}

std::vector<unsigned char> VBO::getPixels() const
{
    newTimer("getPixels");
    // Bind the multisampled FBO for reading
    glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, this->vboId);
    // Bind the normal FBO for drawing
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, this->resolveVboId);
    // Blit the multisampled FBO to the normal FBO
    glBlitFramebufferEXT(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    // Bind the normal FBO for reading
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, this->resolveVboId);
    std::vector<unsigned char>
        data(width * height * 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
        data.data());
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer
    return data;
}