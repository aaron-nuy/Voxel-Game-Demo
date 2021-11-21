#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>


class EBO
{
public:

	EBO();
	// Constructor that generates a Elements Buffer Object and links it to indices
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

#endif