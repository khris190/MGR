#ifndef VBO_HPP
#define VBO_HPP
#include <GL/glew.h>
#include <cstddef>
#include <sys/types.h>
#include <vector>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
class VBO {
public:
    VBO(uint width, uint height);
    VBO(VBO&&) = delete;
    VBO(const VBO&) = delete;
    VBO& operator=(VBO&&) = delete;
    VBO& operator=(const VBO&) = delete;
    ~VBO();
    size_t getHeight() const { return height; }
    size_t getWidth() const { return width; }
    void bind() const;
    std::vector<unsigned char> getPixels() const;

private:
    GLuint vboId;
    GLuint resolveVboId;
    GLuint textureId;
    GLuint resolveTextureId;
    size_t width, height;
};

#endif // VBO_HPP
