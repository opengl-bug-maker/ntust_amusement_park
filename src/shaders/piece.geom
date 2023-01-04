#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 VStc;
} g_in[];

out GS_OUT{
    vec2 GOtc;
} gs_out;

//uniform float start_time;
//uniform float now_time;
//uniform vec3 explodeCenter;


void main() {
//    GOtc = VStc;
    gl_Position = gl_Position;
    gs_out.GOtc = g_in[0].VStc;
    EmitVertex();
    gs_out.GOtc = g_in[1].VStc;
    EmitVertex();
    gs_out.GOtc = g_in[2].VStc;
    EmitVertex();
    EndPrimitive();
}