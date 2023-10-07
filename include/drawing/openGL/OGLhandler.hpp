#ifndef OGLHANDLER_HPP
#define OGLHANDLER_HPP

#include "drawing/openGL/shaders/Triangle2.hpp"
#include "objects/window.hpp"
#include "shaders/Triangle.hpp"
#include <GL/glcorearb.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

// TODO this doesnt need to be a singleton
class OGLhandler {
public:
    Shaders::Triangle* triangleShader;
    Shaders::Triangle2* newTriangleShader;
    Window* mainWindow;
    GLuint fboID;

    // static OGLhandler* getInstance(int width = 0, int height = 0);
    OGLhandler(int width, int height);
    ~OGLhandler();
    /**
     * Singletons should not be cloneable.
     */
    OGLhandler(OGLhandler& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const OGLhandler&) = delete;
    void initOGL();
    void initFramebuffer();

protected:
    // static OGLhandler* instance_;
};

#endif // OGLHANDLER_HPP
