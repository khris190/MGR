#include "OGLhandler.hpp"
#include "drawing/openGL/shaders/Triangle.hpp"

void errorCallback(int error, const char* description) { std::cerr << "Error: " << description << std::endl; }

OGLhandler* OGLhandler::getInstance(int width, int height)
{
    if (instance_ == nullptr) {
        instance_ = new OGLhandler(width, height);
    }
    return instance_;
}
void OGLhandler::initOGL() { }

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // kolor (RGBA) uzywany do czyszczenia bufora koloru
    triangleShader = new Shaders::Triangle();
    triangleShader->useShader();
    // setupShaders();
}
OGLhandler::~OGLhandler()
{
    delete mainWindow;
    delete triangleShader;
}

OGLhandler* OGLhandler::instance_;
