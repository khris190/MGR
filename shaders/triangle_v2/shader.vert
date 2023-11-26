#version 460 core

// TODO optimize in variables
layout(location = 0) in float fPosition;
layout(location = 1) in float fZPos;
layout(location = 2) in vec2 v2fTrianglePos;
layout(location = 3) in float fRotation;
layout(location = 4) in vec4 v4fColor;

uniform mat2 scaleMatrix;

out vec4 vertexColor;

void main()
{
    mat2 RotationMatrix = mat2(
        cos(fRotation), -sin(fRotation), //
        sin(fRotation), cos(fRotation) //
    );
    vec2 ScreenspaceTrianglePos = ((v2fTrianglePos * 2.0f) - 1.0f);
    vec2 PointOffset = ((vec2(fPosition, 0.f) * RotationMatrix) * scaleMatrix);
    // out
    gl_Position = vec4(ScreenspaceTrianglePos + PointOffset, fZPos, 1.f);
    vertexColor = v4fColor;
}