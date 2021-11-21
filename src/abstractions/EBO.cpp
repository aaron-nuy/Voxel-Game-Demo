#include"EBO.h"

EBO::EBO() {
		glGenBuffers(1, &ID);
}

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void EBO::Load(std::vector<GLuint>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Load(GLuint* indices, GLsizeiptr size) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

GLuint EBO::getID()
{
	return ID;
}