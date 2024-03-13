#include "Context.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

Context::Context(const int &width, const int &height, const char *title,
                 GLFWmonitor *monitor, const bool &hidden) {
  if (hidden) {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  }
  this->windows.push_back(Window(width, height, title, monitor));
  currentWindow = 0;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Blad: " << glewGetErrorString(err) << std::endl;
    exit(1);
  }
  int major, minor;
  glfwGetVersion(&major, &minor, nullptr);
  if (major != 4, minor != 6) {
    std::cout << major << " " << minor << std::endl;
    std::cerr << "Brak obslugi OpenGL 4.6\n";
    exit(2);
  }
}

void Context::addWindow(const int &width, const int &height, const char *title,
                        GLFWmonitor *monitor, const bool &hidden) {
  if (hidden) {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  }
  this->windows.push_back(
      Window(width, height, title, monitor, this->windows[0].getWindow()));
  currentWindow = this->windows.size() - 1;
}

const Window &Context::getWindow(int64_t index) const {
  if (index < this->windows.size()) {
    return this->windows[index];
  } else {
    throw std::out_of_range("index out of range of windows vector");
  }
}
