#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include "../objects/Window.hpp"
#include "drawing/openGL/shaders/AbstractShader.hpp"

class Context {
public:
    Context(const int& width, const int& height, const char* title, GLFWmonitor* monitor = nullptr, const bool& hidden = false);
    Context(Context&&) = delete;
    Context(const Context&) = delete;
    Context& operator=(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    ~Context() = default;

    void addWindow(const int& width, const int& height, const char* title, GLFWmonitor* monitor = nullptr, const bool& hidden = false);
    const Window& getWindow(int64_t index) const;

protected:
    Context() = default;

private:
    std::vector<Window> windows;
    std::vector<shaders::AbstractShader> shaders;
    // TODO
    //  Buffer mainBuffer;
    int64_t currentWindow = -1;
};

#endif // CONTEXT_HPP
