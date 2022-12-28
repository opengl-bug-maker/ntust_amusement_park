#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture_coordinate;

out V_OUT {
   vec3 color;
   vec2 texture_coordinate;
} v_out;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {
    //gl_Position = vec4(position, 1.0f);
    //gl_Position = u_model * vec4(position, 1.0f);
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
    v_out.texture_coordinate = vec2(texture_coordinate.x, 1.0f - texture_coordinate.y);
    v_out.color = color;
}