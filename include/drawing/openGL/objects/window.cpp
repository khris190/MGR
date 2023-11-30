
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glcorearb.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <iostream>
#include "window.hpp"

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
    : height(height)
    , width(width)
{

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // inicjacja wersji kontekstu
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // incicjacja profilu rdzennego
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_RED_BITS, 8); // 8 bits for red channel
    glfwWindowHint(GLFW_GREEN_BITS, 8); // 8 bits for green channel
    glfwWindowHint(GLFW_BLUE_BITS, 8); // 8 bits for blue channel
    glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for alpha channel

    this->window = glfwCreateWindow(width, height, title, monitor, share);

    if (!this->window) {
        glfwTerminate(); // konczy dzialanie biblioteki GLFW
        exit(EXIT_FAILURE);
    }

    // glfwSetKeyCallback(window, keyCallback); // rejestracja funkcji zwrotnej do oblsugi klawiatury

    this->makeCurrent();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(0); // v-sync on

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
void Window::swapBuffer() const { glfwSwapBuffers(this->window); }
void Window::bindFramebuffer() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); }
void Window::makeCurrent() const { glfwMakeContextCurrent(this->window); }
//@SuppressWarnings("squid:S125")
void Window::cleanWindow() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color to a light blue
    glClear(GL_COLOR_BUFFER_BIT); // czyszczenie bufora koloru
}

void Window::loadExtensions() const
{
    if (glewIsExtensionSupported("GL_ARB_blend_func_extended")) {
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    } else {
        std::cerr << "Brak obslugi GL_ARB_blend_func_extended\n";
        exit(3);
    }
}

Window::~Window()
{
    glfwDestroyWindow(this->window); // niszczy okno i jego kontekst
}
