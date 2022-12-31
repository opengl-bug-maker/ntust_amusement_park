#version 410 core
out vec4 f_color;

in V_OUT {
   vec3 color;
   vec2 texture_coordinate;
} f_in;
uniform sampler2D u_texture1;
uniform sampler2D u_texture;

void main()
{
    f_color = vec4(f_in.color*0.34, 1.0f);
    //f_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    f_color = texture(u_texture, f_in.texture_coordinate)+f_color;
}

