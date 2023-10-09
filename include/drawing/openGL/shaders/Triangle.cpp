#include "Triangle.hpp"
#include "common/DataStructures.hpp"
#include <exception>
inline myData::position rotate(float x, float y, float angle)
{
    return myData::position(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}
// TODO fix if works
namespace shaders {
GLuint Triangle::VertexInput::vPositionLoc = 0;
GLuint Triangle::VertexInput::vColorLoc = 0;
Triangle::Triangle(int height, int width, float Scale)
    : AbstractShader("shaders/triangle/shader.vert", "shaders/triangle/shader.frag")
{
    VertexInput::vPositionLoc = glGetAttribLocation(shaderProgram, "vPosition");
    VertexInput::vColorLoc = glGetAttribLocation(shaderProgram, "vColor");
    this->height = height;
    this->width = width;
    this->Scale = Scale;
    stride = sizeof(VertexInput);
}

Triangle::~Triangle()
{
    glDeleteProgram(shaderProgram); // usuniecie programu cieniowania
}
void Triangle::setShaderAttributes()
{
    glEnableVertexAttribArray(VertexInput::vPositionLoc);
    glVertexAttribPointer(
        VertexInput::vPositionLoc, glm::vec3::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, vPosition)) //
    );
    glEnableVertexAttribArray(VertexInput::vColorLoc);
    glVertexAttribPointer(
        VertexInput::vColorLoc, glm::vec4::length(), GL_FLOAT, GL_FALSE, stride,
        (void*)(offsetof(VertexInput, vColor)) //
    );
}
int Triangle::bindDataToBuffer(Genotype& genes)
{
    newTimer("prepareTriangles CPU");
    std::vector<VertexInput> vInputs = std::vector<VertexInput>();
    int i = 0;
    int max = genes.genes.size();
    vInputs.reserve(max * 6);
    for (auto gene : genes.genes) {
        if (gene.type_of_shape == myData::ShapeType::triangle) {
            glm::vec4 color = { gene.color.r, gene.color.g, gene.color.b, gene.color.a };
            float x = (gene.position.x * this->width);
            float y = (gene.position.y * this->height);

            float scaleX = gene.scale.x * Scale * this->width;
            float scaleY = gene.scale.y * Scale * this->height;
            float rotation = gene.rotation * 3.14;
            myData::position p1, p2;
            if (rotation != 0) {
                p1 = rotate(0, scaleY, rotation * 2);
                p2 = rotate(scaleX, 0, rotation * 2);
            }
            p1.move(x, y);
            p2.move(x, y);
            float distance = 1.f / max;

            // rescale to -1 : 1
            x = x / (float)(this->width) * 2 - 1;
            y = y / (float)(this->height) * 2 - 1;
            p2.x = p2.x / (float)(this->width) * 2 - 1;
            p2.y = p2.y / (float)(this->height) * 2 - 1;
            p1.x = p1.x / (float)(this->width) * 2 - 1;
            p1.y = p1.y / (float)(this->height) * 2 - 1;
            vInputs.emplace_back(
                glm::vec3(x, y, distance * i - 1.f),
                color //
            );
            vInputs.emplace_back(
                glm::vec3(p1.x, p1.y, distance * i - 1.f),
                color //
            );
            vInputs.emplace_back(
                glm::vec3(p2.x, p2.y, distance * i - 1.f),
                color //
            );
        }
        i++;
    }
    glBufferData(GL_ARRAY_BUFFER, stride * vInputs.size(), vInputs.data(), GL_STATIC_DRAW);
    this->setShaderAttributes();
    return vInputs.size();
}

} // namespace shaders
