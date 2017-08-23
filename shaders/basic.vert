#version 410 core

in  vec3    position;
in  vec3    normal;
in  vec2    uv;
in  float   matIndex;

out vec3    fposition;
out vec3    fnormal;
out vec2    fuv;
out float   fmatIndex;

void main() {
    fposition = position;
    fnormal = normal;
    fuv = uv;
    fmatIndex = matIndex;
	gl_Position = vec4(position, 1.0);
}