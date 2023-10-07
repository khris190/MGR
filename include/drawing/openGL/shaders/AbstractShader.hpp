#ifndef ABSTRACTSHADER_HPP
#define ABSTRACTSHADER_HPP

#include "genetic/Genotype.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace Shaders {
class AbstractShader {
public:
    AbstractShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    virtual ~AbstractShader() = 0;
    virtual void setShaderAttributes() = 0;
    virtual int bindDataToBuffer(Genotype& genes) = 0;
    GLuint shaderProgram;
    void* data;
    int stride;

    void useShader()
    {
        glUseProgram(shaderProgram);
    }

private:
    void printProgramInfoLog(GLuint program);
    std::string loadShaderSource(const std::string& shaderPath);
    void printShaderInfoLog(GLuint shader);
    bool compileShader(const std::string& shaderPath, GLenum shaderType, GLuint& shaderID);
};
} // namespace Shaders

#endif // ABSTRACTSHADER_HPP
