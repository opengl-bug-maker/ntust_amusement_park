#version 410 core
out vec4 FragColor;

in GS_OUT{
    vec2 TexCoords; 
    vec3 color;
} f_in;
uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, f_in.TexCoords)+vec4(1.0f, 1.0f, 0.0f, 1.0);
}
