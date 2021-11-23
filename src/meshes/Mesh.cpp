#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO _mVBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO _mEBO(indices);
	// Links VBO attributes such as coordinates and colors to VAO
	_mVAO.LinkAttrib(_mVBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	_mVAO.LinkAttrib(_mVBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	_mVAO.LinkAttrib(_mVBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	_mVAO.LinkAttrib(_mVBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	_mVAO.Unbind();
	_mVBO.Unbind();
	_mEBO.Unbind();
}


void Mesh::Draw(Shader& shader,Player& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	_mVAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		
		std::string num;
		std::string type = textures[i].getType();
		if ((type == "diffuse") || (type == "baseColor"))
		{
			num = std::to_string(numDiffuse++);
		}
		else if ((type == "specular") || (type == "metallicRoughness"))
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].Bind();
		textures[i].Assign(shader, (type + num).c_str(), i);
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.getID(), "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
