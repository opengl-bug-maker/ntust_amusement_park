#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices =7) out;
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
    float bias = 1;
    float delta_time = now_time-start_time;
    gl_Position = gl_in[0].gl_Position;
    if(delta_time>160){
        if(gs_in[0].texture_coordinate[0]>gs_in[0].texture_coordinate[1]){
            gl_Position+=vec4(bias, bias, 0, 0);
        }
        else{
            gl_Position+=vec4(-bias, -bias, 0, 0);
        }
    }
    gs_out.texture_coordinate = gs_in[0].texture_coordinate;
    gs_out.color = gs_in[0].color;

    gs_out.texture_coordinate = gs_in[0].texture_coordinate;
    //gs_out.color = gs_in[0].color+vec3(1.0f, 1.0f, 1.0f);
    gs_out.time = delta_time;
    EmitVertex();


    gl_Position = gl_in[1].gl_Position;
    if(delta_time>160){
        if(gs_in[0].texture_coordinate[0]>gs_in[0].texture_coordinate[1]){
            gl_Position+=vec4(bias, bias, 0, 0);
        }
        else{
            gl_Position+=vec4(-bias, -bias, 0, 0);
        }
    }
    gs_out.texture_coordinate = gs_in[1].texture_coordinate;
    gs_out.color = gs_in[1].color;

    gs_out.texture_coordinate = gs_in[1].texture_coordinate;
    //gs_out.color = gs_in[1].color+vec3(1.0f, 1.0f, 1.0f);
    gs_out.time = delta_time;
    EmitVertex();


    gl_Position = gl_in[2].gl_Position;
    if(delta_time>160){
        if(gs_in[0].texture_coordinate[0]>gs_in[0].texture_coordinate[1]){
            gl_Position+=vec4(bias, bias, 0, 0);
        }
        else{
            gl_Position+=vec4(-bias, -bias, 0, 0);
        }
    }
    gs_out.texture_coordinate = gs_in[2].texture_coordinate;
    gs_out.color = gs_in[2].color;
    gs_out.texture_coordinate = gs_in[2].texture_coordinate;
    gs_out.time = delta_time;
    EmitVertex();
    EndPrimitive();

}

// run dont close