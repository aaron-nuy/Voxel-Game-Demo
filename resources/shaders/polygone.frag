#version 330 core

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D diffuse0;

in vec2 texUV;

void main()
{
	// outputs final color
	FragColor = color;
}