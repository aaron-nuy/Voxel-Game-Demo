#include"VBO.h"

VBO::VBO() {
	glGenBuffers(1, &ID);
}

VBO::VBO(std::vector<Vertex>& vertices) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(std::vector<glm::mat4>& mat4s) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, mat4s.size() * sizeof(glm::mat4), mat4s.data(), GL_STATIC_DRAW);
}

VBO::VBO(std::vector<Vertex3>& vertices) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex3), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

GLuint VBO::getID()
{
	return ID;
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::Load(std::vector<Vertex3>& vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Load(GLfloat* vertices, GLsizeiptr size) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
