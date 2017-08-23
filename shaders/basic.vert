#version 400

in vec3 position;
in vec3 normal;
in vec2 uv;

void main() {
	gl_Position = vec4(position, 1.0);
}