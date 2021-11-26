#pragma once

#include"../dependencies/stb_image.h"
#include"shaderClass.h"

class Texture3D
{
public:
	Texture3D();

	void loadTexture3D(const std::string* mapSides);
	// Assigns
	void Assign(Shader& shader, const char* uniform);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();

	GLuint getID();
	const char* getType();

	void setType(const char* type);
private:
	GLuint ID;
	const char* type;
};