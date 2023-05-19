#ifndef __SHADERS_H__
#define __SHADERS_H__
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace shaders
{
    std::string loadShaderSource(const std::string &shaderPath);
    bool createShader(const std::string &shaderPath, GLenum shaderType, GLuint &shaderID);
    void printShaderInfoLog(GLuint shader);
    void printProgramInfoLog(GLuint program);
    bool setupShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath, GLuint &shaderProgram);
} // namespace shaders

#endif /* __SHADERS_H__ */