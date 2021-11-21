#include"Texture.h"

Texture::Texture() {
	type = "diffuse";
	unit = 0;
}
Texture::Texture(const char* image, const char* texType, GLuint slot)
{
	// Assigns the type of the texture ot the texture object
	type = texType;
	unit = slot;
	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Check what type of color channels the texture has and load it accordingly
	switch (numColCh) {
	case 4:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
		break; 		
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
		break;
	case 1:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
		break;
	default:
		throw std::invalid_argument("Automatic Texture type recognition failed");
		break;
	}

	// Generates MipMaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Assign(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.getID(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

GLuint Texture::getID()
{
	return ID;
}

GLuint Texture::getUnit()
{
	return unit;
}

const char* Texture::getType()
{
	return type;
}

void Texture::setType(const char* type)
{
	this->type = type;
}

void Texture::setUnit(GLuint slot)
{
	this->unit = slot;
}
