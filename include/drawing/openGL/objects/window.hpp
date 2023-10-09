#include <GLFW/glfw3.h>
#include <cstddef>
class Window {
public:
    Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    void swapBuffer() const;
    void makeCurrent() const;
    void cleanWindow() const;
    ~Window();

    int getHeight() const { return height; }
    int getWidth() const { return width; }

private:
    GLFWwindow* window;
    int height;
    int width;
};