#version 410 core
out vec4 f_color;

in V_OUT {
   vec3 color;
} f_in;

void main()
{
    f_color = vec4(f_in.color, 1.0f);
    //f_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

