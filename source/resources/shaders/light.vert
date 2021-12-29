#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 lmodel;
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * lmodel * vec4(aPos, 1.0f);
}