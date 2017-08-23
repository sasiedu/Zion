#version 400 core

in  vec3    fposition;
in  vec3    fnormal;
in  vec2    fuv;
in  float   fmatIndex;

uniform sampler2D   textures[10];
uniform bool        isTexture[10];
uniform vec4        texColor[10];

out vec4 out_color;

void main() {
    int i = 0;
    for (; i < 10; i++)
    {
        if (i == int(fmatIndex))
            break;
    }
	vec4 color = texColor[i];
    if (isTexture[i])
    {
        if (i == 0)
            color *= texture(textures[0], fuv);
    }
	out_color = color;
}