#version 330 core

out vec4 FragColor;

uniform vec4 color;
uniform int isTextured;
uniform sampler2D diffuse0;

in vec2 tex;

void main()
{
	// outputs final color
	if(bool(isTextured) && (texture(diffuse0,tex).a<0.3f)){
		discard;
	}
	FragColor = isTextured*texture(diffuse0,tex) +  int(!bool(isTextured))*color;
}