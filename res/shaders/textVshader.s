#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 textcord;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = textcord;
    gl_Position = projection * model * vec4(position, 1.0);
}