#include "Mesh.hpp"
#include "my_utils/Profiler.hpp"
#include <memory>

// TODO !!!! remove/update VAO
bool Mesh::addVao(std::shared_ptr<shaders::AbstractShader> shader, Genotype& genes, GLenum mode)
{
    newTimer("addVao");
    drawMode.push_back(mode);

    vao.push_back(0);
    buffers.push_back(0);
    glGenVertexArrays(1, &vao.back()); // generowanie identyfikatora VAO
    glGenBuffers(1, &buffers.back()); // generowanie identyfikatorow VBO

    glBindVertexArray(vao.back());
    // VBO dla wspolrzednych i kolorow
    glBindBuffer(GL_ARRAY_BUFFER, buffers.back());

    // glBufferData(GL_ARRAY_BUFFER, stride*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    vaoVerticies.push_back(shader->bindDataToBuffer(genes));

    return true;
}

void Mesh::drawVAO(GLenum mode)
{
    for (size_t i = 0; i < vao.size(); i++) {
        glBindVertexArray(vao[i]);
        glDrawArrays(mode, 0, vaoVerticies[i]);
    }
}

void Mesh::drawVAO()
{
    for (size_t i = 0; i < vao.size(); i++) {
        glBindVertexArray(vao[i]);
        glDrawArrays(drawMode[i], 0, vaoVerticies[i]);
    }
}

void Mesh::drawLastVAO(GLenum mode)
{
    int i = vao.size() - 1;
    glBindVertexArray(vao[i]);
    glDrawArrays(mode, 0, vaoVerticies[i]);
}

void Mesh::drawLastVAO()
{
    int i = vao.size() - 1;
    glBindVertexArray(vao[i]);
    glDrawArrays(drawMode[i], 0, vaoVerticies[i]);
}

void Mesh::clear()
{
    glDeleteVertexArrays(vao.size(), &vao.front());
    glDeleteBuffers(buffers.size(), &buffers.front());
    vao.clear();
    buffers.clear();
    vaoVerticies.clear();
}