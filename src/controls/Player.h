#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"../abstractions/ShaderClass.h"


class Player
{	
public:

	Player(glm::vec3 position);
	void UpdateMatrix(GLfloat FOV, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar);
	void Matrix(Shader& shader, const char* uniform);
	void MoveFor();
	void MoveBack();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void MoveForFPS();
	void MoveBackFPS();

	void setSpeed(glm::vec3 speed);
	void setSpeedX(GLfloat speed);
	void setSpeedY(GLfloat speed);
	void setSpeedZ(GLfloat speed);
	void setPositionY(float newY);
	void setOrientation(glm::vec3 orientation);
	glm::vec3 getUp();
	glm::vec3 getSpeed();
	glm::vec3 getPosition();
	glm::vec3 getOrientation();
private:
	glm::vec3 Speed;


	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	GLfloat zNear, zFar;
	const glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
};

