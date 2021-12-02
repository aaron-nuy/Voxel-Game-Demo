#pragma once
#include"VAO.h"
#include"EBO.h"
#include"ShaderClass.h"
#include"Texture.h"

class Polygone
{
	GLuint numberOfVertices;
	VAO _mVAO;
	VBO _mVBO;
	Shader* _mShader;

public:
	Polygone(Shader* shader,GLfloat radius, GLfloat numberOfSides);
	void Draw(glm::vec2 position, GLfloat aspectRatio);

};

