	#pragma once
#include<string>

#include"../abstractions/EBO.h"
#include"../abstractions/VAO.h"
#include"../abstractions/Texture.h"
#include"../controls/Player.h"


enum Mode {
	Triangles = GL_TRIANGLES,
	LineLoop = GL_LINE_LOOP,
	LineStrip = GL_LINE_STRIP,
	LineStripAdj = GL_LINE_STRIP_ADJACENCY,
	Lines = GL_LINES
};


class CubeMesh {
public:
	GLfloat vertices[24] = {
		-0.501f,-0.501f, 0.501f,	//0
		 0.501f,-0.501f, 0.501f,	//1
		 0.501f,-0.501f,-0.501f,	//2
		-0.501f,-0.501f,-0.501f,	//3
		-0.501f, 0.501f, 0.501f,	//4
		 0.501f, 0.501f, 0.501f,	//5 
		 0.501f, 0.501f,-0.501f,	//6
		-0.501f, 0.501f,-0.501f	//7
	};
	GLuint indices[24] = {

		0,1,
		1,2,
		2,3,
		3,0,
		0,4,
		4,5,
		5,6,
		6,7,
		7,4,
		1,5,
		2,6,
		3,7
		/* // Bottom 
		0,1,2,
		2,3,0,
		// Left
		0,3,7,
		7,4,0,
		// Back
		7,3,2,
		2,6,7,
		// Right
		6,2,1,
		1,5,6,
		// Top
		6,5,4,
		4,7,6,
		// Front
		0,4,5,
		5,1,0*/
	};



	CubeMesh();
	void setMode(GLenum mode);
	void Draw( Player& camera, GLFWwindow* window);
	void passTransformMatrix(glm::mat4 TransformMatrix);

private:
	GLenum mode = Lines;
	Shader* _mShader;
	VAO _mVAO;
};