	#pragma once
#include<string>

#include"../abstractions/EBO.h"
#include"../abstractions/VAO.h"
#include"../abstractions/Texture.h"
#include"../controls/Player.h"
#include"../abstractions/Texture3D.h"


enum Mode {
	Triangles = GL_TRIANGLES,
	LineLoop = GL_LINE_LOOP,
	LineStrip = GL_LINE_STRIP,
	LineStripAdj = GL_LINE_STRIP_ADJACENCY,
	Lines = GL_LINES
};


class CubeMesh {
public:
	GLfloat skyVertices[24] = {
		//   Coordinates
		-1.0f, -1.0f,  1.0f,//        7--------6
		 1.0f, -1.0f,  1.0f,//       /|       /|
		 1.0f, -1.0f, -1.0f,//      4--------5 |
		-1.0f, -1.0f, -1.0f,//      | |      | |
		-1.0f,  1.0f,  1.0f,//      | 3------|-2
		 1.0f,  1.0f,  1.0f,//      |/       |/
		 1.0f,  1.0f, -1.0f,//      0--------1
		-1.0f,  1.0f, -1.0f
	};

	GLfloat vertices[24] = {
		-0.501f,-0.501f, 0.501f,	//0
		 0.501f,-0.501f, 0.501f,	//1
		 0.501f,-0.501f,-0.501f,	//2
		-0.501f,-0.501f,-0.501f,	//3
		-0.501f, 0.501f, 0.501f,	//4
		 0.501f, 0.501f, 0.501f,	//5 
		 0.501f, 0.501f,-0.501f,	//6
		-0.501f, 0.501f,-0.501f		//7
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

	GLuint skyIndices[36] = {
		// Right
		1, 2, 6,
		6, 5, 1,
		// Left
		0, 4, 7,
		7, 3, 0,
		// Top
		4, 5, 6,
		6, 7, 4,
		// Bottom
		0, 3, 2,
		2, 1, 0,
		// Back
		0, 1, 5,
		5, 4, 0,
		// Front
		3, 7, 6,
		6, 2, 3
	};


	CubeMesh();
	CubeMesh(Texture3D* text, Shader* shader);
	void setMode(GLenum mode);
	void Draw( Player& camera, GLFWwindow* window);
	void Draw( Player& camera, GLFWwindow* window,float aspectRatio);
	void passTransformMatrix(glm::mat4 TransformMatrix);

private:
	GLenum mode = Lines;
	Shader* _mShader;
	Texture3D* _mTexture = NULL;
	VAO _mVAO;
};