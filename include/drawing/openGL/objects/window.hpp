#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
    void swapBuffer() const;
    void bindFramebuffer() const;
    void makeCurrent() const;
    void cleanWindow() const;
    void loadExtensions() const;
    ~Window();

    int getHeight() const { return height; }
    int getWidth() const { return width; }

private:
    GLFWwindow* window;
    int height;
    int width;
};