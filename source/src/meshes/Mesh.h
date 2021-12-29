#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"../abstractions/VAO.h"
#include"../abstractions/EBO.h"
#include"../abstractions/Texture.h"
#include"../controls/Player.h"

class Mesh
{
public:
	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader,  Player& camera);

private:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	VAO VAO;
};
#endif