#version 410 core
out vec4 f_color;

in GS_OUT{
    vec2 GOtc;
} fs_in;

uniform sampler2D u_texture;

void main() {
    f_color = texture(u_texture, fs_in.GOtc);
}

