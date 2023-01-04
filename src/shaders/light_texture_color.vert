#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec3 color;
layout (location = 2) in vec2 texture_coordinate;
//layout (location = 3) in vec2 texture_coordinate;
out V_OUT {
    vec3 color;
    vec3 normal;
    vec2 texture_coordinate;
    vec3 FragPos;
} v_out;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {

    v_out.FragPos = vec3(u_model * vec4(position, 1.0));
    v_out.normal = mat3(transpose(inverse(u_model))) * normal;
    v_out.color = color;
    v_out.texture_coordinate = texture_coordinate;
    gl_Position = u_projection * u_view * vec4(v_out.FragPos, 1.0);
}