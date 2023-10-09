#include "fullscreenFBO.hpp"
#include <array>

namespace shaders {

FullscreenFBO::FullscreenFBO(GLuint fboID)
    : AbstractShader("shaders/fullscreenFBO/fullscreenFBO.vert", "shaders/fullscreenFBO/fullscreenFBO.frag")
{
    glActiveTexture(GL_TEXTURE0); // Choose a texture unit (GL_TEXTURE0, GL_TEXTURE1, etc.)
    glBindTexture(GL_TEXTURE_2D, fboID); // Bind the FBO texture to the chosen unit
    glUniform1i(glGetUniformLocation(this->shaderProgram, "fboTexture"), 0); // Set the uniform for the FBO texture
}

FullscreenFBO::~FullscreenFBO() = default;

void FullscreenFBO::setShaderAttributes()
{
    // empty
}

int FullscreenFBO::bindDataToBuffer(Genotype& genes)
{
    this->useShader();
    GLuint fullscreenQuadVAO;
    GLuint fullscreenQuadVBO;

    // Vertices for a fullscreen quad (two triangles)
    std::array<float, 12> quadVertices = {
        // Positions
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f, //

        -1.0f, 1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f, //
    };

    // Create and bind the VAO
    glGenVertexArrays(1, &fullscreenQuadVAO);
    glBindVertexArray(fullscreenQuadVAO);

    // Create and bind the VBO (Vertex Buffer Object)
    glGenBuffers(1, &fullscreenQuadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, fullscreenQuadVBO);

    // Copy the vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices.data(), GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // Draw the quad
    glDrawArrays(GL_TRIANGLES, 0, 6); // Assuming you have a quad setup as two triangles

    // Unbind the VBO and VAO
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the FBO texture if necessary

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 1;
}

} // namespace shaders
