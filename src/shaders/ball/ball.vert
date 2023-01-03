#version 410 core

layout (location = 0) in vec4 Position;
out vec3 vPosition;

void main()
{
    vPosition = Position.xyz;
}