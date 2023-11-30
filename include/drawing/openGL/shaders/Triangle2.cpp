#include "Triangle2.hpp"
#include "common/Config.hpp"
#include "my_utils/Profiler.hpp"
#include <cstddef>

namespace shaders {

Triangle2::Triangle2()
    : AbstractShader("shaders/triangle_v2/shader.vert", "shaders/triangle_v2/shader.frag")
{

    auto scale = Config::get<Config::Argument::SCALE>();
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "scaleMatrix");
    stride = sizeof(VertexInput);
    VertexInput::fPositionLoc = glGetAttribLocation(shaderProgram, "fPosition");
    VertexInput::fZPosLoc = glGetAttribLocation(shaderProgram, "fZPos");
    VertexInput::v2fTrianglePosLoc = glGetAttribLocation(shaderProgram, "v2fTrianglePos");
    VertexInput::fRotationLoc = glGetAttribLocation(shaderProgram, "fRotation");
    VertexInput::v4fColorLoc = glGetAttribLocation(shaderProgram, "v4fColor");
    glUseProgram(shaderProgram);
    glUniformMatrix2fv(
        vertexColorLocation,
        1,
        true,
        glm::value_ptr(
            glm::mat2(
                scale, 0,
                0, scale //
                ) //
            ) //
    );
}

void Triangle2::setShaderAttributes()
{
    glEnableVertexAttribArray(VertexInput::fPositionLoc);
    glVertexAttribPointer(
        VertexInput::fPositionLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, fPosition)) //
    );
    glEnableVertexAttribArray(VertexInput::fZPosLoc);
    glVertexAttribPointer(
        VertexInput::fZPosLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, fZPos)) //
    );
    glEnableVertexAttribArray(VertexInput::v2fTrianglePosLoc);
    glVertexAttribPointer(
        VertexInput::v2fTrianglePosLoc, glm::vec2::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, v2fTrianglePos)) //
    );
    glEnableVertexAttribArray(VertexInput::fRotationLoc);
    glVertexAttribPointer(
        VertexInput::fRotationLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, fRotation)) //
    );
    glEnableVertexAttribArray(VertexInput::v4fColorLoc);
    glVertexAttribPointer(
        VertexInput::v4fColorLoc, glm::vec4::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, v4fColor)) //
    );
}
int Triangle2::bindDataToBuffer(Genotype& genes)
{
    newTimer("Triangle2::bindDataToBuffer");
    int max = genes.genes.size();
    std::vector<VertexInput> vInputs = std::vector<VertexInput>();
    vInputs.reserve(max * 3);
    int i = 0;
    for (auto gene : genes.genes) {
        glm::vec4 color = { gene.color.r, gene.color.g, gene.color.b, gene.color.a };
        float distance = 1.f / (float)max;

        vInputs.emplace_back(
            0,
            distance * (float)i - 1.f,
            glm::vec2(gene.position.x, gene.position.y),
            0,
            color //
        );

        vInputs.emplace_back(
            gene.scale.x,
            distance * (float)i - 1.f,
            glm::vec2(gene.position.x, gene.position.y),
            gene.rotation * 3.14 * 2,
            color //
        );

        vInputs.emplace_back(
            gene.scale.y,
            distance * (float)i - 1.f,
            glm::vec2(gene.position.x, gene.position.y),
            gene.rotation * 3.14 * 2 + 3.14 / 2,
            color //
        );
        i++;
    }
    newTimer("Triangle2::bindDataToBuffer glBufferData");

    glBufferData(GL_ARRAY_BUFFER, stride * vInputs.size(), vInputs.data(), GL_DYNAMIC_DRAW); // slow
    this->setShaderAttributes();
    return vInputs.size();
}

Triangle2::~Triangle2()
{
    glDeleteProgram(shaderProgram); // usuniecie programu cieniowania
}

} // namespace shaders
