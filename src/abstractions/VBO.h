#pragma once

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<vector>


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
	GLuint getID();

	void Load(std::vector<Vertex3>& vertices);
	void Load(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
private:
	GLuint ID;
};
