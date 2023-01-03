#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture_coordinate;
//layout (location = 3) in vec3 vertex_coord;

out VS_OUT {
   vec2 texture_coordinate;
   vec3 color;
} v_out;

uniform vec3 cameraPosition;
uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main() {

//    vec3 dir = position + vertex_coord - cameraPosition;
//    dir = normalize(dir);
//    vec2 hor = vec2(dir.zx);
//
//    double st = dir.y;
//    double ct = length(hor);
//
//    hor = normalize(hor);
//    double sp = -hor.y;
//    double cp = hor.x;
//
//    mat4 face = mat4(
//    cp,  st * sp, -ct * sp, 0,
//    0,       ct,       st, 0,
//    sp, -st * cp, ct * cp, 0,
//    0,        0,       0,1
//    );



    //gl_Position = vec4(position, 1.0f);
    //gl_Position = u_model * vec4(position, 1.0f);
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
//    gl_Position = u_projection * u_view * u_model * vec4(position + vertex_coord, 1.0f);
//    gl_Position = vec4(position, 1.0f);
//    gl_Position = u_projection * u_view * u_model * (vec4(position, 0) + inverse(face) * vec4(vertex_coord, 1.0f));
    //v_out.texture_coordinate = vec2(texture_coordinate.x, 1.0f - texture_coordinate.y);
    v_out.texture_coordinate = texture_coordinate;
    v_out.color = color;
}