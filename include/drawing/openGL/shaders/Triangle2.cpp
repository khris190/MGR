#include "Triangle2.hpp"
#include "common/Config.hpp"
#include <cstddef>

// TODO fix if works
namespace Shaders {

// TODO?
GLuint Triangle2::VertexInput::vPositionLoc = 0;
GLuint Triangle2::VertexInput::vZPosLoc = 0;
GLuint Triangle2::VertexInput::trianglePosLoc = 0;
GLuint Triangle2::VertexInput::rotationLoc = 0;
GLuint Triangle2::VertexInput::vColorLoc = 0;
Triangle2::Triangle2()
    : AbstractShader("shaders/triangle_v2/shader.vert", "shaders/triangle_v2/shader.frag")
{

    auto scale = Config::get<Config::Argument::SCALE>();
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "scaleMatrix");
    stride = sizeof(VertexInput);
    VertexInput::vPositionLoc = glGetAttribLocation(shaderProgram, "vPosition");
    VertexInput::vZPosLoc = glGetAttribLocation(shaderProgram, "vZPos");
    VertexInput::trianglePosLoc = glGetAttribLocation(shaderProgram, "trianglePos");
    VertexInput::rotationLoc = glGetAttribLocation(shaderProgram, "rotation");
    VertexInput::vColorLoc = glGetAttribLocation(shaderProgram, "vColor");
    glUseProgram(shaderProgram);
    glUniformMatrix2fv(
        vertexColorLocation,
        1,
        true,
        glm::value_ptr(
            glm::mat2(
                scale, 0, //
                0, scale //
                ) //
            ) //
    );
}

void Triangle2::setShaderAttributes()
{
    glEnableVertexAttribArray(VertexInput::vPositionLoc);
    glVertexAttribPointer(
        VertexInput::vPositionLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, vPosition)) //
    );
    glEnableVertexAttribArray(VertexInput::vZPosLoc);
    glVertexAttribPointer(
        VertexInput::vZPosLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, vZPos)) //
    );
    glEnableVertexAttribArray(VertexInput::trianglePosLoc);
    glVertexAttribPointer(
        VertexInput::trianglePosLoc, glm::vec2::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, trianglePos)) //
    );
    glEnableVertexAttribArray(VertexInput::rotationLoc);
    glVertexAttribPointer(
        VertexInput::rotationLoc, 1, GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, rotation)) //
    );
    glEnableVertexAttribArray(VertexInput::vColorLoc);
    glVertexAttribPointer(
        VertexInput::vColorLoc, glm::vec4::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, vColor)) //
    );
}
int Triangle2::bindDataToBuffer(Genotype& genes)
{
    newTimer("prepareTriangles GPU");
    int max = genes.genes.size();
    std::vector<VertexInput> vInputs = std::vector<VertexInput>();
    vInputs.reserve(max * 3);
    int i = 0;
    for (auto gene : genes.genes) {
        if (gene.type_of_shape == myData::ShapeType::triangle) {
            glm::vec4 color = { gene.color.r, gene.color.g, gene.color.b, gene.color.a };
            float distance = 1.f / max;

            vInputs.emplace_back(
                0,
                distance * i - 1.f,
                glm::vec2(gene.position.x, gene.position.y),
                0,
                color //
            );

            vInputs.emplace_back(
                gene.scale.x,
                distance * i - 1.f,
                glm::vec2(gene.position.x, gene.position.y),
                gene.rotation * 3.14 * 2,
                color //
            );

            vInputs.emplace_back(
                gene.scale.y,
                distance * i - 1.f,
                glm::vec2(gene.position.x, gene.position.y),
                gene.rotation * 3.14 * 2 + 3.14 / 2,
                color //
            );
        }
        i++;
    }

    glBufferData(GL_ARRAY_BUFFER, stride * vInputs.size(), vInputs.data(), GL_DYNAMIC_DRAW); // slow
    this->setShaderAttributes();
    return vInputs.size();
}

Triangle2::~Triangle2()
{
    glDeleteProgram(shaderProgram); // usuniecie programu cieniowania
}

} // namespace Shaders
