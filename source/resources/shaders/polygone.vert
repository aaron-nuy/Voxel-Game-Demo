#version 330 core

// Positions/Coordinates
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 texUV;
uniform mat4 transform;
uniform mat4 rotation;
uniform float scale;
uniform float aspectRatio;

out vec2 tex;

void main(){
	
	tex= texUV;
	// Outputs the positions/coordinates of all vertices
	vec4 scaleView = (  int(aspectRatio > 1 ) * vec4( 1.0f/aspectRatio, 1.0f, 1.0f, 1.0f )
				      + int(aspectRatio <=1 ) * vec4( 1.0f, 1.0f*aspectRatio, 1.0f, 1.0f ) ) ;
	gl_Position =  transform*(rotation*vec4(scale*aPos,-0.1f,1.0f) * scaleView);

}