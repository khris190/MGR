#ifndef OGLHANDLER_HPP
#define OGLHANDLER_HPP

#include "drawing/openGL/shaders/AbstractShader.hpp"
#include "drawing/openGL/shaders/Triangle2.hpp"
#include "objects/window.hpp"
#include "shaders/Triangle.hpp"
#include <GL/glcorearb.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class OGLhandler {
public:
    std::shared_ptr<shaders::AbstractShader> triangleShader;
    std::shared_ptr<shaders::AbstractShader> newTriangleShader;
    Window* mainWindow;
    GLuint fboID;

    OGLhandler(int width, int height);
    ~OGLhandler();
    void initOGL();
    void initFramebuffer();
};

#endif // OGLHANDLER_HPP
