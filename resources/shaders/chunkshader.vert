#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texUV;

// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Imports the camera matrix
uniform mat4 camMatrix;

uniform mat4 transform;


void main()
{	
	// calculates current position
	crntPos = vec3(transform*vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = normals;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = texUV;
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix *vec4(crntPos, 1.0);
}