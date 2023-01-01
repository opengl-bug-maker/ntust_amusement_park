#version 330 core
out vec4 f_color;

in V_OUT {
   vec2 texture_coordinate;
   vec3 color;
} f_in;

uniform sampler2D u_texture;

void main()
{
    f_color = vec4(f_in.color, 1.0f);
    //f_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    f_color = texture(u_texture, f_in.texture_coordinate)*f_color;
    //f_color = texture(u_texture, f_in.texture_coordinate)+f_color;
    //f_color = f_color;
    //f_color.a = 0.05f;
    //f_color = vec4(1.0f, 0.33f, 0.33, 1.0f);
}

