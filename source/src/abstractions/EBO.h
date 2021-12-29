#pragma once

#include"../dependencies/glad.h"
#include<vector>

class EBO
{
public:

	EBO();
	EBO(std::vector<GLuint>& indices);
	EBO(GLuint* indices, GLsizeiptr size);

	// Loads data into EBO
	void Load(std::vector<GLuint>& indices);
	void Load(GLuint* indices, GLsizeiptr size);

	GLuint getID();
	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
private:
	// ID reference of Elements Buffer Object
	GLuint ID;
};
