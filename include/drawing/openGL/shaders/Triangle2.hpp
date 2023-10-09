
#ifndef TRIANGLE2_HPP
#define TRIANGLE2_HPP

#include "AbstractShader.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace shaders {
class Triangle2 : public AbstractShader {

public:
    struct VertexInput {
        float vPosition; // Equivalent to layout(location = 0) in vec2 vPosition;
        float vZPos; // Equivalent to layout(location = 1) in float vZPos;
        glm::vec2 trianglePos; // Equivalent to layout(location = 2) in vec2 trianglePos;
        float rotation; // Equivalent to layout(location = 3) in float rotation;
        glm::vec4 vColor; // Equivalent to layout(location = 5) in vec4 vColor;

        VertexInput(float position, float zPos, glm::vec2 rotate, float rot, glm::vec4 color)
            : vPosition(position)
            , vZPos(zPos)
            , trianglePos(rotate)
            , rotation(rot)
            , vColor(color)
        {
        }
        static GLuint vPositionLoc;
        static GLuint vZPosLoc;
        static GLuint trianglePosLoc;
        static GLuint rotationLoc;
        static GLuint vColorLoc;
    };

    Triangle2();
    Triangle2(Triangle2&&) = default;
    Triangle2(const Triangle2&) = default;
    Triangle2& operator=(Triangle2&&) = default;
    Triangle2& operator=(const Triangle2&) = default;
    ~Triangle2();
    void setShaderAttributes() override;
    int bindDataToBuffer(Genotype& genes) override;
};

} // namespace shaders

#endif // TRIANGLE_HPP
