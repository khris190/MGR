
#ifndef TRIANGLE2_HPP
#define TRIANGLE2_HPP

#include "AbstractShader.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace shaders {
class Triangle2 : public AbstractShader {

public:
    struct VertexInput {
        float fPosition; // Equivalent to layout(location = 0) in vec2 fPosition;
        float fZPos; // Equivalent to layout(location = 1) in float fZPos;
        glm::vec2 v2fTrianglePos; // Equivalent to layout(location = 2) in vec2 v2fTrianglePos;
        float fRotation; // Equivalent to layout(location = 3) in float fRotation;
        glm::vec4 v4fColor; // Equivalent to layout(location = 5) in vec4 v4fColor;

        VertexInput(float position, float zPos, glm::vec2 rotate, float rot, glm::vec4 color)
            : fPosition(position)
            , fZPos(zPos)
            , v2fTrianglePos(rotate)
            , fRotation(rot)
            , v4fColor(color)
        {
        }
        inline static GLuint fPositionLoc = 0;
        inline static GLuint fZPosLoc = 0;
        inline static GLuint v2fTrianglePosLoc = 0;
        inline static GLuint fRotationLoc = 0;
        inline static GLuint v4fColorLoc = 0;
    };

    Triangle2();
    Triangle2(Triangle2&&) = default;
    Triangle2(const Triangle2&) = default;
    Triangle2& operator=(Triangle2&&) = default;
    Triangle2& operator=(const Triangle2&) = default;
    ~Triangle2() override;
    void setShaderAttributes() override;
    int bindDataToBuffer(Genotype& genes) override;
};

} // namespace shaders

#endif // TRIANGLE_HPP
