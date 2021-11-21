#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>

#include"../dependencies/stb_image.h"
#include"shaderClass.h"

class Texture
{
public:

	Texture();
	Texture(const char* image, const char* texType, GLuint slot);

	// Assigns a texture unit to a texture
	void Assign(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();

	GLuint getID();
	GLuint getUnit();
	const char* getType();

	void setType(const char* type);
	void setUnit(GLuint slot);

private:
	GLuint ID;
	const char* type;
	GLuint unit;
};
#endif