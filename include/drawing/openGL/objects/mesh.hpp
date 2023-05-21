#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>

#include <glm/glm.hpp>
#include "../shaders/shaders.hpp"
#include "my_utils/Logger.hpp"

namespace mesh
{
    extern std::vector<GLuint> vao;
    extern std::vector<int> vaoVerticies;
    extern std::vector<GLuint> buffers; // identyfikatory obiektow VBO
    extern std::vector<float[8]> vertices;
    extern std::vector<GLenum> drawMode;

    extern GLuint shaderProgram;
    extern GLuint vertexLoc;
    extern GLuint colorLoc;

    bool AddVao(std::vector<float> vertices, GLuint shaderProgram, GLenum mode);

    void DrawVAO(GLenum mode);
    void DrawVAO();
    void DrawLastVAO(GLenum mode);
    void DrawLastVAO();
    void Clear();
} // namespace mesh

#endif // MESH_HPP
