#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, TexCoords)+vec4(0.3, 0.1, 0.22, 1.0);
}
