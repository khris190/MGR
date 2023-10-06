#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Shaders
{
    class IShader
    {
    public:
        IShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        virtual ~IShader() = 0;
        GLuint shaderProgram;

        void useShader() { glUseProgram(shaderProgram); }
    };
    void printProgramInfoLog(GLuint program);
    std::string loadShaderSource(const std::string& shaderPath);
    void printShaderInfoLog(GLuint shader);
    bool compileShader(const std::string& shaderPath, GLenum shaderType, GLuint& shaderID);
} // namespace Shaders
