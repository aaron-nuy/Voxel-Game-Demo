#pragma once
#include"Chunk.h"
#include<GLFW/glfw3.h>

class ChunkManager
{

public:
	static const unsigned char _mRenderingDistance = 4;
	std::vector<std::vector<std::shared_ptr<Chunk>>> chunkList;

	ChunkManager(Shader* shader, Texture* text, GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos);

	void GenerateX(GLfloat freq, GLfloat depth);
	void GenerateMX(GLfloat freq, GLfloat depth);
	void GenerateZ(GLfloat freq, GLfloat depth);
	void GenerateMZ(GLfloat freq, GLfloat depth);
	void manageChunks();
	void manageChunk(int i, int j);
	void Draw(Player& player, GLFWwindow* window);

	bool isInBoundaries(glm::vec3 position);

	void setBlock(glm::vec3 position, BlockID block);
	unsigned char getRenderDistance();

	unsigned char getBlock(glm::vec3 position);
	glm::vec3 getCurrentChunk(glm::vec3 Pos);
	glm::vec3 getPositionInChunk(glm::vec3 Pos);
private:
	Shader* _mShader;
	Texture* _mTexture;
};

