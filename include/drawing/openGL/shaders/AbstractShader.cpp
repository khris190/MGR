#include "AbstractShader.hpp"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace shaders {
AbstractShader::AbstractShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    shaderProgram = glCreateProgram(); // utworzenie identyfikatora programu cieniowania

    GLuint vertexShader;
    if (!compileShader(vertexShaderPath, GL_VERTEX_SHADER, vertexShader)) {
        glDeleteProgram(shaderProgram);

        std::cerr << "Unable to compile vertex shader (" << vertexShaderPath << ")\n";
        exit(EXIT_FAILURE);
    }

    GLuint fragmentShader;
    if (!compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER, fragmentShader)) {
        glDeleteShader(vertexShader);
        glDeleteProgram(shaderProgram);

        std::cerr << "Unable to compile fragment shader (" << fragmentShaderPath << ")\n";
        exit(EXIT_FAILURE);
    }

    glAttachShader(shaderProgram, vertexShader); // dolaczenie shadera wierzcholkow
    glAttachShader(shaderProgram, fragmentShader); // dolaczenie shadera fragmentow

    glLinkProgram(shaderProgram); // linkowanie programu cieniowania

    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == 0) {

        printProgramInfoLog(shaderProgram); // wyswietlenie logu linkowania

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        std::cerr << "Unable to link shader (" << vertexShaderPath << ", " << fragmentShaderPath << ")\n";
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

AbstractShader::~AbstractShader() = default;

/*------------------------------------------------------------------------------------------
** funkcja wyswietla zawartosc logu programu cieniowania
** program - identyfikator programu cieniowania
**------------------------------------------------------------------------------------------*/
void AbstractShader::printProgramInfoLog(GLuint program)
{
    int infologLength = 0;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0) {
        int charsWritten = 0;
        std::vector<char> infoLog(infologLength + 1);

        glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
    }
}

/*------------------------------------------------------------------------------------------
** funkcja wczytujaca z pliku kod zrodlowy shadera
** shaderPath - nazwa pliku z kodem zrodlowym shadera
** funkcja zwraca stringa z kodem zrodlowym shadera
**------------------------------------------------------------------------------------------*/
std::string AbstractShader::loadShaderSource(const std::string& shaderPath)
{
    std::ifstream file;
    file.open(shaderPath, std::ios::in);

    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku: " << shaderPath << std::endl;
        return "";
    }

    std::stringstream shaderStream;

    shaderStream << file.rdbuf();

    file.close();

    return shaderStream.str();
}

void AbstractShader::printShaderInfoLog(GLuint shader) const
{
    int infologLength = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 0) {
        int charsWritten = 0;
        std::vector<char> infoLog(infologLength + 1);

        glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
    }
}

bool AbstractShader::compileShader(const std::string& shaderPath, GLenum shaderType, GLuint& shaderID)
{
    bool result = true;
    shaderID = glCreateShader(shaderType);

    std::string source = loadShaderSource(shaderPath);

    if (!source.empty()) {
        const char* shaderSource = source.c_str();
        glShaderSource(shaderID, 1, &shaderSource, nullptr);

        glCompileShader(shaderID);

        GLint compileStatus;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus == 0) {
            std::cerr << "Blad przy kompilacji: " << shaderPath << std::endl;
            printShaderInfoLog(shaderID);

            result = false;
            glDeleteShader(shaderID);
        }
    } else {
        result = false;
        glDeleteShader(shaderID);
    }

    return result;
}
} // namespace shaders
