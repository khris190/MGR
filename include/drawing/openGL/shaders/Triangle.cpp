#include "Triangle.hpp"
#include <exception>

// TODO fix if works
namespace Shaders
{

    Triangle::Triangle(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
        : IShader(vertexShaderPath, fragmentShaderPath)
    {
        vertexLoc = glGetAttribLocation(shaderProgram, "vPosition");
        colorLoc = glGetAttribLocation(shaderProgram, "vColor");
    }

    Triangle::~Triangle()
    {
        glDeleteProgram(shaderProgram); // usuniecie programu cieniowania
    }

} // namespace Shaders
