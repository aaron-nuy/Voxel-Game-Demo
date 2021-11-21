#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D diffuse0;

void main()
{
	// outputs final color
	if(texture(diffuse0,texCoord).a <0.5f){
		discard;
	}
	FragColor = texture(diffuse0,texCoord);
}