#include "Player.h"

Player::Player(glm::vec3 position) {
	Position = position;
}

// Update projection matrix
void Player::UpdateMatrix(GLfloat FOV, GLfloat aspectRatio, GLfloat zNear, GLfloat zFar) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	this->zNear = zNear;
	this->zFar = zFar;
	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOV), aspectRatio, zNear, zFar);

	cameraMatrix = proj * view;
}
void Player::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(shader.GetUniID(uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Player::setSpeed(glm::vec3 speed)
{
	Speed = speed;
}
void Player::setSpeedX(GLfloat speed)
{
	Speed.x = speed;
}
void Player::setSpeedY(GLfloat speed)
{
	Speed.y = speed;
}
void Player::setSpeedZ(GLfloat speed)
{
	Speed.z = speed;
}
void Player::MoveFor()
{
	Position.x += Speed.x * Orientation.x;
	Position.z += Speed.z * Orientation.z;
	Position.y += Speed.y * Orientation.y;
}
void Player::MoveBack()
{	
	Position.x -= Speed.x * Orientation.x;
	Position.z -= Speed.z * Orientation.z;
	Position.y -= Speed.y * Orientation.y;
}
void Player::MoveRight()
{
	Position.x += Speed.x * glm::normalize(glm::cross(Orientation, Up)).x;
	Position.z += Speed.z * glm::normalize(glm::cross(Orientation, Up)).z;
}
void Player::MoveLeft()
{
	Position.x += Speed.x * -glm::normalize(glm::cross(Orientation, Up)).x;
	Position.z += Speed.z * -glm::normalize(glm::cross(Orientation, Up)).z;
}
void Player::MoveUp() {
	Position.y += Speed.y;
}
void Player::MoveDown() {
	Position.y -= Speed.y;
}
// Back and forward movement in free cam mode
void Player::MoveForFPS()
{
	Position.x += Speed.x * Orientation.x;
	Position.z += Speed.z * Orientation.z;
}
void Player::MoveBackFPS()
{
	Position.x -= Speed.x * Orientation.x;
	Position.z -= Speed.z * Orientation.z;
}

glm::vec3 Player::getUp() {
	return Up;
}
glm::vec3 Player::getSpeed() {
	return Speed;
}
glm::vec3 Player::getPosition() {
	return Position;
}
glm::vec3 Player::getOrientation() {
	return Orientation;
}
void Player::setPositionY(float newY) {
	this->Position.y = newY;
}
void Player::setOrientation(glm::vec3 orientation) {
	Orientation = orientation;
}