#version 330 core

layout(location = 0) in vec3 vPosition;

layout(location = 1) in vec4 vColor;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(vPosition, 1.f);
    vertexColor = vColor;
}