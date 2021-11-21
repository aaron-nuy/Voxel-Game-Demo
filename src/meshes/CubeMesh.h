#pragma once
#include<string>

#include"../abstractions/VAO.h"
#include"../abstractions/EBO.h"
#include"../abstractions/Texture.h"
#include"../controls/Player.h"


class CubeMesh {
public:
	GLuint indicesArray[36] = {
		// Bottom 
		0,1,2,
		2,3,0,
		// Left
		6,4,5,
		5,7,6,
		// Back
		9,8,10,
		10,11,9,
		// Right
		15,13,12,
		12,14,15,
		// Top
		18,17,16,
		16,19,18,
		// Front
		23,21,20,
		20,22,23
	};


	std::vector <Vertex3> vertices;
	std::vector <GLuint> indices;
	std::vector <glm::mat4> instancesTransformMatrix;

	CubeMesh(Shader* shader);
	CubeMesh(Shader* shader,Texture* text);
	CubeMesh(Shader* shader, Texture* text, GLuint instance, std::vector <glm::mat4> instanceTransformMatrix);
	
	GLenum getMode();
	GLuint getInstances();
	bool isActivef();
	void setMode(GLenum mode);
	void setInstances(GLuint instances);
	void setActive(bool active);

	void Draw( Player& camera, GLFWwindow* window);
	void DrawInstanced( Player& camera, GLFWwindow* window);
	void passTransformMatrix(std::vector <glm::mat4> instanceTransformMatrix, GLuint instace);

private:
	bool isActive = 0;
	GLenum mode = GL_TRIANGLES;
	GLuint instances = 1;
	Texture* _mTexture;
	Shader* _mShader;
	VAO VAO;
	Vertex3 verticesArray[24] = {
	Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},		//0 0
	Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},		//1 1
	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},		//2 2 Bottom
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f,-1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},		//3 3

	Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},		//0 4
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},		//3 5
	Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},		//4 6 Left
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},		//7 7

	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 0.0f)},		//2 8
	Vertex3{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 0.0f)},		//3 9
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 1.0f)},		//6 10 Back
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 1.0f)},		//7 11

	Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},		//1 12
	Vertex3{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},		//2 13
	Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},		//5 14 Right
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},		//6 15

	Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},		//4 16 Top
	Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},		//5 17
	Vertex3{glm::vec3(0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},		//6 18
	Vertex3{glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},		//7 19

	Vertex3{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},		//0 20
	Vertex3{glm::vec3(0.5f,-0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},		//1 21
	Vertex3{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},		//4 22 Front
	Vertex3{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)} 	    //5 23

	};
};