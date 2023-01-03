#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 20) out;

in VS_OUT {
    vec2 texCoords;
    vec3 color;
} gs_in[];

out GS_OUT{
    vec2 TexCoords; 
    vec3 color;
} gs_out;

uniform float start_time;
uniform float now_time;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(5*(now_time-start_time)) + 1.0) / 2.0) * magnitude; 
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
    gl_Position = gl_in[0].gl_Position;
    gs_out.TexCoords = gs_in[0].texCoords;
    gs_out.color = vec3(1.0f, 0.0f, 0.0f);
    //gs_out.TexCoords = gs_in[0].texCoords;
    //gs_out.color = gs_in[0].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gs_out.TexCoords = gs_in[1].texCoords;
    gs_out.color = vec3(0.0f, 1.0f, 0.0f);
    //gs_out.TexCoords = gs_in[1].texCoords;
    //gs_out.color = gs_in[1].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gs_out.TexCoords = gs_in[2].texCoords;
    gs_out.color = vec3(0.0f, 0.0f, 1.0f);
    //gs_out.TexCoords = gs_in[2].texCoords;
    //gs_out.color = gs_in[2].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();


    vec3 normal = GetNormal();
    gl_Position = gl_in[0].gl_Position;
    gs_out.TexCoords = gs_in[0].texCoords;
    gs_out.color = vec3(1.0f, 0.0f, 0.0f);
    //gs_out.TexCoords = gs_in[0].texCoords;
    //gs_out.color = gs_in[0].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gs_out.TexCoords = gs_in[1].texCoords;
    gs_out.color = vec3(0.0f, 1.0f, 0.0f);
    //gs_out.TexCoords = gs_in[1].texCoords;
    //gs_out.color = gs_in[1].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gs_out.TexCoords = gs_in[2].texCoords;
    gs_out.color = vec3(0.0f, 0.0f, 1.0f);
    //gs_out.TexCoords = gs_in[2].texCoords;
    //gs_out.color = gs_in[2].color+vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();


    EndPrimitive();
}

// run dont close