#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
	vec4 pos = projection*view*vec4(3*aPos,1.0f);
	texCoords = vec4(aPos.x,aPos.y,-aPos.z,1.0f);
	gl_Position = vec4(pos.x,pos.y,pos.w,pos.w);

}