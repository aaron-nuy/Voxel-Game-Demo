#pragma once

#include"../dependencies/glad.h"
#include<glm/glm.hpp>
#include<vector>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;


struct  Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 textCoord;
};
struct Vertex3 {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUVs;
};

class VBO {
public:
	VBO();
	VBO(std::vector<Vertex> &vertices);
	VBO(std::vector<Vertex3> &vertices);
	VBO(std::vector<glm::mat4> &mat4s);
	VBO(GLfloat* vertices, GLsizeiptr size);
	VBO(Vertex3* vertices, GLsizeiptr size);
	GLuint getID();

	void Load(std::vector<Vertex3>& vertices);
	void Load(std::vector<GLfloat>& vertices);
	void Load(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
private:
	GLuint ID;
};
