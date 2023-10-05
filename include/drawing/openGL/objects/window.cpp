#include "window.hpp"
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    // TODO think about moving it
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

    this->width = width;
    this->height = height;
    this->window = glfwCreateWindow(width, height, title, monitor, share);
}

void Window::swapBuffer() { glfwSwapBuffers(this->window); }
void Window::makeCurrent() { glfwMakeContextCurrent(this->window); }

Window::~Window()
{
    glfwDestroyWindow(this->window); // niszczy okno i jego kontekst
}
