#pragma once
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"

class Quad2D
{
	GLuint crossHairArrayIndices[6] = {
		0,1,2,
		2,3,0
	};

	VAO VAO;
	VBO VBO;
	EBO EBO;
	Texture* _mTexture;
	Shader* _mShader;


public:
	Quad2D(Shader* shader,Texture* texture,GLfloat size);
	void Draw(GLfloat aspectRatio);


};

