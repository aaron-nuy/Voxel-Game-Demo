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
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec4 color = glm::vec4(1.0f);
	GLfloat scale = 1.0f;

public:
	Polygone(Shader* shader,GLfloat radius, GLfloat numberOfSides);
	void Draw(glm::vec4 color, glm::vec2 position, GLfloat angle, GLfloat scale, GLfloat aspectRatio);
	void Draw(glm::vec2 position, GLfloat aspectRatio);
	void Draw(GLfloat aspectRatio);

};

