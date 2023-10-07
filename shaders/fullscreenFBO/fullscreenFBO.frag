#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D fboTexture; // The FBO texture

void main()
{
    FragColor = texture(fboTexture, TexCoords);
}