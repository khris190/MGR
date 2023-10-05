#include <GLFW/glfw3.h>
#include <cstddef>
class Window
{
public:
    Window(int width, int height, const char* title, GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
    void swapBuffer();
    void makeCurrent();
    ~Window();

private:
    GLFWwindow* window;
    int height;
    int width;
};