#include"Texture3D.h"

Texture3D::Texture3D(const std::string* mapSides) {
	loadTexture3D(mapSides);
};

void Texture3D::loadTexture3D(const std::string* mapSides)
{
	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	//	Activates Texture
	glActiveTexture(GL_TEXTURE0);
	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// Reads the image from a file and stores it in bytes
	for (GLuint i = 0; i < 6; i++) {
		stbi_set_flip_vertically_on_load(false);
		int widthImg, heightImg, numColCh;
		unsigned char* bytes = stbi_load(mapSides[i].c_str(), &widthImg, &heightImg, &numColCh, 0);
		if (bytes) {
			switch (numColCh) {
			case 4:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
				break;
			case 1:
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
				break;
			default:
				throw std::invalid_argument("Automatic Texture type recognition failed");
				break;
			}
			
			stbi_image_free(bytes);
		}
		else {
			std::cout << "Failed to load texture: " << mapSides[i] << std::endl;
			stbi_image_free(bytes);
		}
		
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void Texture3D::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}
void Texture3D::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
void Texture3D::Delete()
{
	glDeleteTextures(1, &ID);
}

GLuint Texture3D::getID()
{
	return ID;
}

const char* Texture3D::getType()
{
	return type;
}

void Texture3D::setType(const char* type)
{
	this->type = type;
}

void Texture3D::Assign(Shader& shader, const char* uniform) {
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.getID(), uniform);
	// Sets the value of the uniform
	glUniform1i(texUni, 0);
}