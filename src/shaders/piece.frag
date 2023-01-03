#version 410 core
out vec4 f_color;

in vec2 tc;
uniform sampler2D u_texture;

void main() {
    f_color = texture(u_texture, tc);
}

