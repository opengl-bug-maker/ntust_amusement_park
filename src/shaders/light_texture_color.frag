#version 440 core
out vec4 f_color;

in V_OUT {
    vec3 color;
    vec3 normal;
    vec2 texture_coordinate;
    vec3 FragPos;
} f_in;

uniform sampler2D u_texture;

void main()
{
    vec3 light_pos = vec3(0.0f, 30.0f, 30.0f);
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    // diffuse
    vec3 norm = normalize(f_in.normal);
    vec3 lightDir = normalize(light_pos - f_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 light_result = diffuse;
    f_color = 0.8*texture(u_texture, f_in.texture_coordinate)*vec4(light_result, 1.0f)+0.2*texture(u_texture, f_in.texture_coordinate);
    //f_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //f_color = texture(u_texture, f_in.texture_coordinate);
}

