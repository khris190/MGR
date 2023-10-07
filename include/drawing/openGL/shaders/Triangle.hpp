
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "AbstractShader.hpp"

namespace Shaders {
class Triangle : public AbstractShader {
public:
    struct VertexInput {
        glm::vec3 vPosition; // Equivalent to layout(location = 0) in vec2 vPosition;
        glm::vec4 vColor; // Equivalent to layout(location = 1) in vec4 vColor;

        VertexInput(glm::vec3 position, glm::vec4 color)
            : vPosition(position)
            , vColor(color)
        {
        }
        static GLuint vPositionLoc;
        static GLuint vColorLoc;
    };
    int height, width;
    float Scale;

    Triangle(int height, int width, float Scale);
    Triangle(Triangle&&) = default;
    Triangle(const Triangle&) = default;
    Triangle& operator=(Triangle&&) = default;
    Triangle& operator=(const Triangle&) = default;
    ~Triangle();
    void setShaderAttributes() override;
    int bindDataToBuffer(Genotype& genes) override;
};

} // namespace Shaders

#endif // TRIANGLE_HPP
