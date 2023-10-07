#version 460 core

// TODO optimize in variables
layout(location = 0) in float vPosition;
layout(location = 1) in float vZPos;
layout(location = 2) in vec2 trianglePos;
layout(location = 3) in float rotation;
layout(location = 4) in vec4 vColor;

uniform mat2 scaleMatrix;

out vec4 vertexColor;

void main()
{
    // translate 0-1 to -1-1 positions
    // create rotation matrix
    mat2 rotationMatrix = mat2(
        cos(rotation), -sin(rotation), //
        sin(rotation), cos(rotation) //
    );
    // out
    gl_Position = vec4(((trianglePos * 2.0f) - 1.0f) + ((vec2(vPosition, 0.f) * rotationMatrix) * scaleMatrix), vZPos, 1.f);
    vertexColor = vColor;
}