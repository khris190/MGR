#include "OGLhandler.hpp"
#include "drawing/openGL/shaders/Triangle2.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
// #include "context/Context.hpp"

void errorCallback(int error, const char* description) { std::cerr << error << " Error: " << description << std::endl; }

void OGLhandler::initOGL() { }

OGLhandler::OGLhandler(int width, int height)
{

    glfwSetErrorCallback(errorCallback); // rejestracja funkcji zwrotnej do obslugi bledow

    if (!glfwInit()) // inicjacja biblioteki GLFW
        exit(EXIT_FAILURE);

    glewExperimental = GL_TRUE;
    this->mainWindow = new Window(width, height, "test");
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Blad: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    if (!__GLEW_VERSION_4_6) {
        std::cerr << "Brak obslugi OpenGL 4.6\n";
        exit(2);
    }
    this->mainWindow->loadExtensions();
    newTriangleShader = std::make_shared<shaders::Triangle2>();
    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    this->drawerVBO = new VBO(width * 25, height * 25);
    // this->drawerWindow = new Window(width * 50, height * 50, "test2");
    // this->drawerWindow->loadExtensions();

    // newTriangleShader2 = std::make_shared<shaders::Triangle2>();
    std::cout << "GLEW = " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "GL_VENDOR = " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER = " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL = " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
OGLhandler::~OGLhandler()
{
    delete mainWindow;
    // delete drawerWindow;
    delete drawerVBO;
    // glDeleteFramebuffers(1, &fboID);

    glfwTerminate(); // konczy dzialanie biblioteki GLFW
}

// OGLhandler* OGLhandler::instance_;