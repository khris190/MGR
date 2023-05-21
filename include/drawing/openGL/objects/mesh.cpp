#include "mesh.hpp"

namespace mesh
{
    std::vector<GLuint> vao;
    std::vector<int> vaoVerticies;
    std::vector<GLuint> buffers; // identyfikatory obiektow VBO
    std::vector<float[8]> vertices;
    std::vector<GLenum> drawMode;

    GLuint shaderProgram;
    GLuint vertexLoc;
    GLuint colorLoc;
    // TODO !!!! remove/update VAO
    bool AddVao(std::vector<float> vertices, GLuint shaderProgram, GLenum mode)
    {
        drawMode.push_back(mode);
        shaderProgram = shaderProgram;
        vertexLoc = glGetAttribLocation(shaderProgram, "vPosition");
        colorLoc = glGetAttribLocation(shaderProgram, "vColor");

        auto i = vertices.size();
        if (i % 8 != 0) {
            logger.LogErr("Verticies are not a multiplication of 8 they need to be 4 position vals and 4 color vals");
            return false;
        }
        vaoVerticies.push_back(i / 8);

        vao.push_back(0);
        buffers.push_back(0);
        glGenVertexArrays(1, &vao.back()); // generowanie identyfikatora VAO
        glGenBuffers(1, &buffers.back()); // generowanie identyfikatorow VBO

        glBindVertexArray(vao.back());
        // VBO dla wspolrzednych i kolorow
        int stride = 8 * sizeof(float); // 8 = 4 wspolrzedne wierzchoka + 4 kanaly koloru
        glBindBuffer(GL_ARRAY_BUFFER, buffers.back());

        // glBufferData(GL_ARRAY_BUFFER, stride*vertices.size(), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, stride * vaoVerticies.back(), vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(vertexLoc);
        glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, stride, 0); // wspolrzedne wierzcholkow
        glEnableVertexAttribArray(colorLoc);
        glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, stride,
          reinterpret_cast<const void*>(4 * sizeof(float))); // kolory wierzcholkow

        return true;
    }

    void DrawVAO(GLenum mode)
    {
        for (size_t i = 0; i < vao.size(); i++) {
            glBindVertexArray(vao[i]);
            glDrawArrays(mode, 0, vaoVerticies[i]);
        }
    }

    void DrawVAO()
    {
        for (size_t i = 0; i < vao.size(); i++) {
            glBindVertexArray(vao[i]);
            glDrawArrays(drawMode[i], 0, vaoVerticies[i]);
        }
    }

    void DrawLastVAO(GLenum mode)
    {
        int i = vao.size() - 1;
        glBindVertexArray(vao[i]);
        glDrawArrays(mode, 0, vaoVerticies[i]);
    }

    void DrawLastVAO()
    {
        int i = vao.size() - 1;
        glBindVertexArray(vao[i]);
        glDrawArrays(drawMode[i], 0, vaoVerticies[i]);
    }

    void Clear()
    {
        glDeleteVertexArrays(vao.size(), &vao.front()); // generowanie identyfikatora VAO
        glDeleteBuffers(buffers.size(), &buffers.front()); // generowanie identyfikatorow VBO }
        vao.clear();
        buffers.clear();
    }
} // namespace mesh