#ifndef MESH_HPP
#define MESH_HPP

#include "drawing/openGL/shaders/AbstractShader.hpp"
#include "my_utils/Logger.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
// thats retarded, was i high?
class Mesh {
    std::vector<GLuint> vao;
    std::vector<int> vaoVerticies;
    std::vector<GLuint> buffers; // identyfikatory obiektow VBO
    std::vector<float[8]> vertices;
    std::vector<GLenum> drawMode;

    GLuint shaderProgram;
    GLuint vertexLoc;
    GLuint colorLoc;

public:
    bool AddVao(Shaders::AbstractShader* shader, Genotype& genes, GLenum mode);

    void DrawVAO(GLenum mode);
    void DrawVAO();
    void DrawLastVAO(GLenum mode);
    void DrawLastVAO();
    void Clear();
}; // namespace mesh

#endif // MESH_HPP
