#version 330 core

// Positions/Coordinates
layout (location = 0) in vec2 aPos;
uniform mat4 transform;
uniform float aspectRatio;

void main(){
	// Outputs the positions/coordinates of all vertices
	gl_Position = transform*( int(aspectRatio>1)*vec4(aPos.x/aspectRatio, aPos.y, 0.1f, 1.0f)
			    			+ int(aspectRatio<=1)*vec4(aPos.x, aPos.y*aspectRatio, 0.1f, 1.0f));
}