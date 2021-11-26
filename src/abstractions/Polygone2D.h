#pragma once
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"

class Polygone2D
{
public:
	VAO VAO;
	VBO VBO;
	EBO EBO;
	Texture* texture;
	Shader* shader;
	float ratio;

	Polygone2D(Texture* text, Shader* shade );
	void Draw(float aspect);
private: 
	GLfloat crossHairArrayVerts[16] = {
		-0.005f, -0.01f, 0.0f, 0.0f,
		-0.005f,  0.01f, 0.0f, 1.0f,
		 0.005f,  0.01f, 1.0f, 1.0f,
		 0.005f, -0.01f, 1.0f, 0.0f
	};
	GLuint crossHairArrayIndices[6] = {
		0,1,2,
		2,3,0
	};
};

