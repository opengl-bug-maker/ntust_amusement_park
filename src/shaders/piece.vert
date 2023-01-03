#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinate;

out vec2 tc;
uniform vec3 cameraPosition;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

//uniform float start_time;
//uniform float now_time;
//uniform vec3 explodeCenter;

void main() {
    vec3 dir = vec3((u_model * vec4(position, 1.0f))) - cameraPosition;
    dir = normalize(dir);
    vec2 hor = vec2(dir.zx);

    double st = dir.y;
    double ct = length(hor);

    hor = normalize(hor);
    double sp = -hor.y;
    double cp = hor.x;

    mat4 face = mat4(
    cp,  st * sp, -ct * sp, 0,
    0,       ct,       st, 0,
    sp, -st * cp, ct * cp, 0,
    0,        0,       0,1
    );

    tc = texture_coordinate;
    gl_Position = u_projection * u_view * u_model * inverse(face) * vec4(position, 1.0f);
}