#include "MovementManager.h"

char signof(float num) {
	return pow(-1, signbit(num));
}
void print(std::string string, float number) {
	std::cout << string + ": " << number << "." << std::endl;
}
glm::vec3 integrify(glm::vec3 vec) {
	vec.x = (int)vec.x;
	vec.y = (int)vec.y;
	vec.z = (int)vec.z;
	return vec;
}
glm::vec3 roundify(glm::vec3 vec) {
	vec.x = round(vec.x);
	vec.y = round(vec.y);
	vec.z = round(vec.z);
	return vec;
}
glm::vec3 floorify(glm::vec3 vec) {
	vec.x = floor(vec.x);
	vec.y = floor(vec.y);
	vec.z = floor(vec.z);
	return vec;
}
bool canPlaceBlock(ChunkManager* chunkManager,glm::vec3 playerPosition , glm::vec3 placeLocation, float playerHeight) {
	return chunkManager->getPositionInChunk(placeLocation) != chunkManager->getPositionInChunk(playerPosition - glm::vec3(0.0f, playerHeight - 0.5f, 0.0f))
		&& chunkManager->getPositionInChunk(placeLocation) != chunkManager->getPositionInChunk(playerPosition + glm::vec3(0.0f, playerHeight - 0.5f, 0.0f));
}

MovementManager::MovementManager(Player* player, ChunkManager* chunkManager, GLFWwindow* window)
{
	this->player = player;
	this->window = window;
	this->chunkManager = chunkManager;
}


void MovementManager::ManageMovement() {
	// Set the speed independent from the framerate
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	glm::vec3 speed = glm::vec3(SpeedMult * deltaTime);
	player->setSpeed(speed);
	orien = player->getOrientation();
	pos = player->getPosition() + glm::vec3(0.5f, 0.0f, 0.5f);
	canMoveRight = 1;
	canMoveForward = 1;
	canMoveBack = 1;
	canMoveLeft = 1;
	isFalling = 1;

	#pragma region MyRegion
	if (firstCall) {
		int height, width;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width / 2, height / 2);
		glfwGetCursorPos(window, &xpos, &ypos);
		pypos = ypos,
		pxpos = xpos;
		xDelta = -Sensitivity * (xpos - pxpos);
		yDelta = -Sensitivity * (ypos - pypos);
		firstCall = false;

	}

	glfwGetCursorPos(window, &xpos, &ypos);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed *= 1.5f;
		player->setSpeed(speed);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		ray = pos;
		ray2 = pos + glm::vec3(0.0f, playerHeight, 0.0f);
		ray3 = pos + glm::vec3(0.0f, -0.5f, 0.0f);
		while (glm::length(ray - pos) < 0.25f) {
			ray += 0.1f * glm::vec3(orien.x, 0, orien.z);
			ray2 += 0.1f * glm::vec3(orien.x, 0, orien.z);
			ray3 += 0.1f * glm::vec3(orien.x, 0, orien.z);
			if (chunkManager->isInBoundaries(ray) && chunkManager->isInBoundaries(ray2) && chunkManager->isInBoundaries(ray3)
			&& (chunkManager->getBlock(ray) != c_Air || chunkManager->getBlock(ray2) != c_Air || chunkManager->getBlock(ray3) != c_Air)) {
				canMoveForward = 0;
				break;
			}
		}
		if (canMoveForward) {
			player->MoveForFPS();
		}	
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		ray = pos;
		ray2 = pos + glm::vec3(0.0f, playerHeight, 0.0f);
		ray3 = pos + glm::vec3(0.0f, -0.5f, 0.0f);
		while (glm::length(ray - pos) < 0.25f) {
			ray -= 0.1f * glm::vec3(orien.x, 0, orien.z);
			ray2 -= 0.1f * glm::vec3(orien.x, 0, orien.z);
			ray3 -= 0.1f * glm::vec3(orien.x, 0, orien.z);
			if (chunkManager->isInBoundaries(ray) && chunkManager->isInBoundaries(ray2) && chunkManager->isInBoundaries(ray3)
			&& (chunkManager->getBlock(ray) != c_Air || chunkManager->getBlock(ray2) != c_Air || chunkManager->getBlock(ray3) != c_Air)) {
				canMoveBack = 0;
				break;
			}
		}
		if (canMoveBack) {
			player->MoveBackFPS();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		ray = pos;
		ray2 = pos + glm::vec3(0.0f, playerHeight, 0.0f);
		ray3 = pos + glm::vec3(0.0f, -0.5f, 0.0f);
		while (glm::length(ray - pos) < 0.25f) {
			ray += 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			ray2 += 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			ray3 += 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			if (chunkManager->isInBoundaries(ray) && chunkManager->isInBoundaries(ray2) && chunkManager->isInBoundaries(ray3)
			&& (chunkManager->getBlock(ray) != c_Air || chunkManager->getBlock(ray2) != c_Air || chunkManager->getBlock(ray3) != c_Air)) {
				canMoveRight = 0;
				break;
			}
		}
		if (canMoveRight) {
			player->MoveRight();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		ray = pos;
		ray2 = pos + glm::vec3(0.0f, playerHeight, 0.0f);
		ray3 = pos + glm::vec3(0.0f, -0.5f, 0.0f);
		while (glm::length(ray - pos) < 0.25f) {
			ray -= 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			ray2 -= 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			ray3 -= 0.1f * glm::normalize(glm::cross(glm::vec3(orien.x, 0, orien.z), player->getUp()));
			if (chunkManager->isInBoundaries(ray) && chunkManager->isInBoundaries(ray2) && chunkManager->isInBoundaries(ray3)
			&& (chunkManager->getBlock(ray) != c_Air || chunkManager->getBlock(ray2) != c_Air || chunkManager->getBlock(ray3) != c_Air)) {
				canMoveLeft = 0;
				break;
			}
		}
		if (canMoveLeft) {
			player->MoveLeft();
		}
	}


	pos = player->getPosition() + glm::vec3(0.5f, 0.5f, 0.5f);
	ray = pos;
	while (glm::length(ray - pos) < playerHeight) {
		ray += 0.001f * glm::vec3(0.0f, 1.0f, 0.0f);
		if (chunkManager->isInBoundaries(ray) && chunkManager->getBlock(ray) != c_Air) {
			canJump = 0;
			break;
		}
	}

	pos = player->getPosition() + glm::vec3(0.5f, 0.5f, 0.5f);
	ray = pos;
	while (glm::length(ray - pos) < playerHeight) {
		ray -= 0.001f * glm::vec3(0.0f, 1.0f, 0.0f);
		if (chunkManager->isInBoundaries(ray) && chunkManager->getBlock(ray) != c_Air) {
			isFalling = 0;
			fallingVelocity = 0;
			isJumping = 0;
			jumpingVelocity = 0;
			jumpTime = 0;
			timePast = 0;
			break;
		}
	}

	if (isFalling) {
		timePast += deltaTime;
		fallingVelocity = -gConst * timePast * timePast;
		if (fallingVelocity < -25.0f*deltaTime) {
			fallingVelocity = -25.0f*deltaTime;
		}	
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !isFalling && !isJumping && canJump) {
		isJumping = 1;
		canJump = 0;
	}
	else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		canJump = 1;
	}

	if (isJumping) {
		isFalling = 1;
		jumpTime += deltaTime;
		jumpingVelocity = 2*jumpTime;
		if (jumpingVelocity > 5 * deltaTime) {
			isJumping = 0;
		}
	}

	player->setPositionY(player->getPosition().y + jumpingVelocity + fallingVelocity);
	pos = player->getPosition() + glm::vec3(0.5f, 0.5f, 0.5f);
	ray = pos;
	while (glm::length(ray - pos) < playerHeight) {
		ray -= 0.001f * glm::vec3(0.0f, 1.0f, 0.0f);
		if (chunkManager->isInBoundaries(ray) && chunkManager->getBlock(ray) != c_Air) {
			player->setPositionY(ray.y + playerHeight - 0.5f);
			break;
		}
	}

	//			Set cursor delta
	xDelta = -Sensitivity * ((xpos - pxpos) / 100);
	yDelta = -Sensitivity * ((ypos - pypos) / 50);
	//			So camera doesn't jerk when looking all the way up or down
	if ((player->getOrientation().y <= -0.99f) && yDelta < 0) {
		yDelta = 0;
		player->setOrientation(glm::vec3(player->getOrientation().x, -0.99f, player->getOrientation().z));
	}
	else if ((player->getOrientation().y >= 0.99f) && yDelta > 0) {
		yDelta = 0;
		player->setOrientation(glm::vec3(player->getOrientation().x, 0.99f, player->getOrientation().z));
	}
	//			Rotates World around the vertical center (horizonal rotation with mouse)
	player->setOrientation(glm::rotate(player->getOrientation(), glm::radians(GLfloat(xDelta)), player->getUp()));
	//			Rotates World around the horizontal center (vertical rotation with mouse)
	player->setOrientation(glm::normalize(player->getOrientation() + glm::vec3(0.0f, glm::radians(yDelta), 0.0f)));
	//			Sets previous cursor position
	pypos = ypos, pxpos = xpos;
	#pragma endregion


	if (canClick) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			orien = player->getOrientation();
			pos = player->getPosition() + glm::vec3(0.5f, 0.5f, 0.5f);
			ray = pos;
			foundBlock = false;
			while (!foundBlock) {
				ray += 0.01f * orien;
				if (chunkManager->isInBoundaries(ray) && chunkManager->getBlock(ray) != c_Air) {
					foundBlock = true;
					glm::vec3 placeAt = glm::vec3(ray - 0.01f * orien);
					if (canPlaceBlock(chunkManager, pos, placeAt, playerHeight)) chunkManager->setBlock(placeAt, c_Stone);
				}
				if (glm::length(ray - pos) > 128.0f) break;
			}
			canClick = false;
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			orien = player->getOrientation();
			pos = player->getPosition()+glm::vec3(0.5f,0.5f,0.5f);
			ray = pos;
			foundBlock = false;
			while (!foundBlock) {
				ray += 0.01f * orien;
				if (chunkManager->isInBoundaries(ray) && chunkManager->getBlock(ray) != c_Air) {
						foundBlock = true;
						chunkManager->setBlock(ray, c_Air);
				}
				if (glm::length(ray - pos) > 128.0f) break;
			}
			canClick = false;
		}
	}
	else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)) {
		canClick = true;
	}
	lastFrame = currentFrame;
}
