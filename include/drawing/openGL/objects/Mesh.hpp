#ifndef MESH_HPP
#define MESH_HPP

#include "drawing/openGL/shaders/AbstractShader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
class Mesh {
    std::vector<GLuint> vao;
    std::vector<int> vaoVerticies;
    std::vector<GLuint> buffers; // identyfikatory obiektow VBO
    std::vector<std::array<float, 8>> vertices;
    std::vector<GLenum> drawMode;

    GLuint shaderProgram;
    GLuint vertexLoc;
    GLuint colorLoc;

public:
    ~Mesh();
    bool addVao(std::shared_ptr<shaders::AbstractShader> shader, Genotype& genes, GLenum mode);

    void drawVAO(GLenum mode);
    void drawVAO();
    void drawLastVAO(GLenum mode);
    void drawLastVAO();
    void clear();
}; // namespace mesh

#endif // MESH_HPP
