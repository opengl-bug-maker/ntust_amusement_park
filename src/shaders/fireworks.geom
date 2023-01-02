#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
//layout (points, max_vertices = 3) out;

in VS_OUT {
    vec2 texture_coordinate;
    vec3 color;
} gs_in[];

out GS_OUT{
    vec2 texture_coordinate;
    vec3 color;
    float time;
} gs_out;
float rand(float x)
{
    float y = fract(sin(x)*100000.0);
    return y;
}
uniform float start_time;
uniform float now_time;
uniform vec2 blast_dir;
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}
vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin((now_time-start_time)) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}
vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {

    vec3 normal = GetNormal();
   // for(float i = 0; i<20.0f; i+=1.0f){
        gl_Position = gl_in[0].gl_Position;

        gs_out.texture_coordinate = gs_in[0].texture_coordinate;
        gs_out.color = gs_in[0].color;
        gs_out.texture_coordinate = gs_in[0].texture_coordinate;
        //gs_out.color = gs_in[0].color+vec3(1.0f, 1.0f, 1.0f);
        gs_out.time = now_time-start_time;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        gs_out.texture_coordinate = gs_in[1].texture_coordinate;
        gs_out.color = gs_in[1].color;
        gs_out.texture_coordinate = gs_in[1].texture_coordinate;
        //gs_out.color = gs_in[1].color+vec3(1.0f, 1.0f, 1.0f);
        gs_out.time = gl_in[0].gl_Position.y;
        EmitVertex();

        gl_Position = gl_in[2].gl_Position;
        gs_out.texture_coordinate = gs_in[2].texture_coordinate;
        gs_out.color = gs_in[2].color;
        gs_out.texture_coordinate = gs_in[2].texture_coordinate;
        //gs_out.color = gs_in[2].color+vec3(1.0f, 1.0f, 1.0f);
        gs_out.time = gl_in[0].gl_Position.y;
        EmitVertex();
   // }


    EndPrimitive();
}

// run dont close