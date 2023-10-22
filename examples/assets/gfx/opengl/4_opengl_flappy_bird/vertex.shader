#version 450 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoords;

layout (location = 0) out vec2 v_TexCoords

layout (binding = 0) uniform Matrices {
    mat4 model;
    mat4 projection;
};

void main() {
	v_TexCoords = a_TexCoords;
    gl_Position = projection * model * vec4(a_Position, 0.0, 1.0);
}