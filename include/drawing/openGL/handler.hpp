#ifndef OGLHANDLER_HPP
#define OGLHANDLER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>

#include "shaders/shaders.hpp"

#include "my_utils/Logger.hpp"

namespace OGLhandler
{
    //******************************************************************************************
    extern GLuint shaderProgram; // identyfikator programu cieniowania

    extern GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
    extern GLuint colorLoc; // lokalizacja atrybutu wierzcholka - kolor

    extern std::array<GLuint, 2> vao; // identyfikatory obiektow VAO
    extern std::array<GLuint, 3> buffers; // identyfikatory obiektow VBO

    extern int width;
    extern int height;

    extern GLFWwindow* window;
    extern GLuint textureID;
    extern GLuint fboID;
    extern GLuint depthrenderbuffer;
    extern GLenum DrawBuffers[1];

    //******************************************************************************************

    void initEngine(int width, int height);
    void draw();
    void errorCallback(int error, const char* description);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cleanup();
    void initGL();
    void setupShaders();
    void setupBuffers();
    void prepareScene();

    // void initGLEW();
    // void initGLFW();

    void setPositionsAndColors();

    void drawVAO(void (*)(GLuint array), size_t arraySize);

} // namespace OGLhandler

#endif // ENGINE_HPP
