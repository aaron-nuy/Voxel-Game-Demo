#version 330 core

// Positions/Coordinates
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texUV;

out vec2 texCoord;


void main(){
	texCoord = texUV;
	// Outputs the positions/coordinates of all vertices
	gl_Position =  vec4(aPos, 0.f, 1.0f);
}