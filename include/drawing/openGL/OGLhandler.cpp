#include "OGLhandler.hpp"
#include "common/Config.hpp"
#include "drawing/openGL/shaders/Triangle.hpp"
#include "drawing/openGL/shaders/Triangle2.hpp"
#include <memory>

void errorCallback(int error, const char* description) { std::cerr << "Error: " << description << std::endl; }

void OGLhandler::initOGL() { }
void OGLhandler::initFramebuffer()
{
    glGenFramebuffers(1, &fboID);
    // glBindFramebuffer(GL_FRAMEBUFFER, fboID);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("unable to complete framebuffer");
    }
}
OGLhandler::OGLhandler(int width, int height)
{
    glfwSetErrorCallback(errorCallback); // rejestracja funkcji zwrotnej do obslugi bledow

    if (!glfwInit()) // inicjacja biblioteki GLFW
        exit(EXIT_FAILURE);

    this->mainWindow = new Window(width, height, "test");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(0); // v-sync on

    // inicjacja GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Blad: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    if (!__GLEW_VERSION_4_6) {
        std::cerr << "Brak obslugi OpenGL 4.6\n";
        exit(2);
    }

    if (glewIsExtensionSupported("GL_ARB_blend_func_extended")) {
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    }

    std::cout << "GLEW = " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "GL_VENDOR = " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL_RENDERER = " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL = " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    initFramebuffer();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // kolor (RGBA) uzywany do czyszczenia bufora koloru
    triangleShader = std::make_unique<shaders::Triangle>(mainWindow->height, mainWindow->width, Config::get<Config::Argument::SCALE>());
    newTriangleShader = std::make_shared<shaders::Triangle2>();
}
OGLhandler::~OGLhandler()
{
    delete mainWindow;
    glDeleteFramebuffers(1, &fboID);
}

// OGLhandler* OGLhandler::instance_;