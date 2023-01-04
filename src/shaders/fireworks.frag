#version 410 core
out vec4 f_color;

in GS_OUT {
   vec2 texture_coordinate;
   vec3 color;
    float time;
} f_in;

uniform sampler2D u_texture;

void main()
{
    f_color = vec4(f_in.color, 1.0f);
    //f_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    f_color = texture(u_texture, f_in.texture_coordinate)*f_color*1.12;
    //f_color = texture(u_texture, f_in.texture_coordinate)+f_color;
    //f_color = f_color;
    //f_color.a = 0.05f;
    //f_color = vec4(1.0f, 0.33f, 0.33, 1.0f);
}

