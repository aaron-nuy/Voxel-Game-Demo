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
	Position += Speed * Orientation;
}
void Player::MoveBack()
{	
	Position -= Speed * Orientation;
}
void Player::MoveRight()
{
	Position += Speed * glm::normalize(glm::cross(Orientation, Up));
}
void Player::MoveLeft()
{
	Position += Speed * -glm::normalize(glm::cross(Orientation, Up));
}
void Player::MoveUp() {
	Position += Speed * Up;
}
void Player::MoveDown() {
	Position -= Speed * Up;
}
// Back and forward movement in free cam mode
void Player::MoveForFPS()
{
	Position += Speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
}
void Player::MoveBackFPS()
{
	Position -= Speed * glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
}

glm::vec3 Player::UpVector() {
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