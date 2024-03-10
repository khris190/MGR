#ifndef OGLHANDLER_HPP
#define OGLHANDLER_HPP

#include "drawing/openGL/objects/VBO.hpp"
#include "drawing/openGL/shaders/AbstractShader.hpp"
#include "objects/Window.hpp"
#include <GL/glcorearb.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

class OGLhandler {
public:
    std::shared_ptr<shaders::AbstractShader> newTriangleShader;
    std::shared_ptr<shaders::AbstractShader> newTriangleShader2;
    Window* mainWindow;
    Window* drawerWindow;
    VBO* drawerVBO;

    OGLhandler(int width, int height);
    ~OGLhandler();
    void initOGL();
    void initFramebuffer();
};

#endif // OGLHANDLER_HPP
