#version 410 core

out vec4 FragColor;
in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in float gPrimitive;
uniform vec3 LightPosition;
uniform vec3 DiffuseMaterial;
uniform vec3 AmbientMaterial;
uniform vec4 color_in;
float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2 * d * d);
    return d;
}

void main()
{
    vec3 light_pos = vec3(0, 30, 30);

    vec3 N = -normalize(gFacetNormal);
    vec3 L = LightPosition;
//    float df = abs(dot(N, L));
    float aaa = dot(N, light_pos);
//    aaa = 1 - exp2(-2 * d * d);
//    aaa = 1/aaa;

    float df = dot(N, L);
//    vec3 color = AmbientMaterial + df * DiffuseMaterial;

    //vec3 color = AmbientMaterial + df*DiffuseMaterial+aaa*vec3(color_in);
    //color_in = 0.5, 0, 0, 1
    vec3 color = 0.01*aaa*vec3(0.33, 0.33,0.33)+0.98*vec3(color_in);

    float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
    float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
    //color = amplify(d1, 40, -0.5) * amplify(d2, 60, -0.5) * color;
//    color = amplify(d1, 40, -0.5) * color;
//    color = amplify(d2, 60, -0.5) * color;

    //FragColor = color_in*vec4(color, 1.0f);

    FragColor = color_in;
    FragColor = vec4(color, 1.0f);
}