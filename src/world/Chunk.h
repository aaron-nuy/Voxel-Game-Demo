#pragma once
#include<glm/gtc/noise.hpp>
#include<vector>
#include<memory>

#include"../abstractions/Texture.h"
#include"../abstractions/VAO.h"
#include"../abstractions/EBO.h"
#include"../controls/Player.h"


enum Block {
	c_Air = 0,
	c_Grass,
	c_Stone,
	c_Dirt
};


// Vertices for different block faces
const std::vector<Vertex3> Bottom = {
	Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.5f, 0.5f)},		//0 
	Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f,-1.0f, 0.0f),  glm::vec2(1.0f, 0.5f)},		//1 
	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f,-1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},		//2  Bottom
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.5f, 1.0f)},		//3 
};
const std::vector<Vertex3> Left = {
	Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f)},		//0 Left
	Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},		//1
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.0f)},		//2
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)},		//3
};
const std::vector<Vertex3> Back = {
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f),  glm::vec2(0.5f, 0.0f)},		//0
	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f),   glm::vec2(0.0f, 0.0f)},		//1
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f),   glm::vec2(0.0f, 0.5f)},		//2 Back
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f),  glm::vec2(0.5f, 0.5f)},		//3
};
const std::vector<Vertex3> Right = {
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.5f)},		//0
	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec2(0.0f, 0.0f)},		//1
	Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec2(0.5f, 0.0f)},		//2
	Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec2(0.5f, 0.5f)},		//3 Right

};
const std::vector<Vertex3> Front = {
Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 0.5f)}, 	   //0				  																										  
Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 0.0f)},		//1
Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),      glm::vec2(0.5f, 0.0f)},		//2
Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f),      glm::vec2(0.5f, 0.5f)},		//3 Front
};
const std::vector<Vertex3> Top = {
	Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},		//0 Top
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.5f)},		//1
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.5f, 0.5f)},		//2
	Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.5f, 1.0f)}		//3
};


class Chunk {
public:
	static const int _mChunkSize = 16;
	static const int _mChunkSizeY = 64;
	long posX = 0, posZ = 0;
	unsigned char Blocks[_mChunkSize][_mChunkSizeY][_mChunkSize] = { 0 };
	VAO _mVAO;
	VBO _mVBO;
	EBO _mEBO;
	std::vector<GLuint> Indices;
	std::vector<Vertex3> Vertices;

	Chunk(GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos);
	// Check which block faces should be rendered and push them into mesh vertices
	void checkFaces();
	// Load chunk mesh into VAO
	void loadVertices();
	// Generate chunk terrain
	void generateTerrain(GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos);
	// Destructor
	~Chunk();
};


