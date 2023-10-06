#ifndef OGLHANDLER_HPP
#define OGLHANDLER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "objects/window.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <array>
#include <GL/glcorearb.h>
#include <stdexcept>
#include "shaders/Triangle.hpp"

// TODO this doesnt need to be a singleton
class OGLhandler
{
public:
    Shaders::Triangle* triangleShader;
    Window* mainWindow;

    static OGLhandler* getInstance(int width = 0, int height = 0);
    /**
     * Singletons should not be cloneable.
     */
    OGLhandler(OGLhandler& other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const OGLhandler&) = delete;
    void initOGL();
    ~OGLhandler();

protected:
    static OGLhandler* instance_;
    OGLhandler(int width, int height);
};

#endif // OGLHANDLER_HPP
