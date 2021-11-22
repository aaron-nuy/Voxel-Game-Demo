#pragma once
#include"../world/ChunkManager.h"
#include"Player.h"


class MovementManager
{
private:	
	Player* player;
	ChunkManager* chunkManager;
	GLFWwindow* window;
	glm::vec3 orien,pos,ray,ray2,ray3;
	double xpos, ypos, pypos, pxpos, yDelta, xDelta;
	double currentFrame, lastFrame = 0.0f;
	float fallingVelocity = 0.0f;
	float jumpingVelocity = 0.0f;
	float deltaTime = 0.0f;
	float timePast = 0.0f;
	float jumpTime = 0.0f;
	float gConst = 1.0f;
	float playerHeight = 1.15f;
	float SpeedMult = 4.0f;
	float Sensitivity = 10.0f;
	int height, width;
	bool canMoveRight = 0;
	bool canMoveForward = 0;
	bool canMoveBack = 0;
	bool canMoveLeft = 0;
	bool isJumping = 0;
	bool isFalling = 0;
	bool canClick = 1;
	bool foundBlock = 0;
	bool firstCall = 1;
	bool canJump = 1;
	bool canCrouch = 1;
public:
	MovementManager(Player* player, ChunkManager* chunkManager, GLFWwindow* window);
	void ManageMovement();
};
