#include "VBO.hpp"
#include <iostream>

VBO::VBO(uint width, uint height)
{
    this->width = width;
    this->height = height;
    glGenFramebuffers(1, &this->vboId);
    glBindFramebuffer(GL_FRAMEBUFFER, this->vboId);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureId, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "error framebuffer";
    }
}

VBO::~VBO()
{
    glDeleteTextures(1, &this->textureId);
    glDeleteFramebuffers(1, &this->vboId);
}

void VBO::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->vboId);
}
