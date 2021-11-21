#include "CubeMesh.h"

CubeMesh::CubeMesh(Shader* shader) {
	instances = 1;
	instancesTransformMatrix.push_back(glm::mat4(1.0));
	_mTexture = NULL;
	_mShader = shader;
	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", _mTexture->getUnit());
	}

	// Loads data from static array to dynamic array ( vector aka arraylist in java)
	// constructor takes data adress (array) and number of elements in it
	vertices.assign(verticesArray, verticesArray + sizeof(verticesArray) / sizeof(Vertex3));
	indices.assign(indicesArray, indicesArray + sizeof(indicesArray) / sizeof(GLuint));

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex3), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex3), (void*)(1 * sizeof(glm::vec3)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}
CubeMesh::CubeMesh(Shader* shader,Texture* text) {
	// Loads data from static array to dynamic array ( vector aka arraylist in java)
	// constructor takes data adress (array) and number of elements in it
	vertices.assign(verticesArray, verticesArray + sizeof(verticesArray) / sizeof(Vertex3));
	indices.assign(indicesArray, indicesArray + sizeof(indicesArray) / sizeof(GLuint));
	_mTexture = text;
	_mShader = shader;
	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", _mTexture->getUnit());
	}

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex3), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex3), (void*)(1 * sizeof(glm::vec3)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex3), (void*)(2 * sizeof(glm::vec3)));
	VBO.Unbind();
	EBO.Unbind();
}
CubeMesh::CubeMesh(Shader* shader,Texture* text , GLuint instance ,std::vector <glm::mat4> instanceTransformMatrix) {
	// Loads data from static array to dynamic array ( vector aka arraylist in java)
	// constructor takes data adress (array) and number of elements in it
	vertices.assign(verticesArray, verticesArray + sizeof(verticesArray) / sizeof(Vertex3));
	indices.assign(indicesArray, indicesArray + sizeof(indicesArray) / sizeof(GLuint));
	_mTexture = text;
	_mShader = shader;
	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", _mTexture->getUnit());
	}

	VAO.Bind();
	VBO VBO(vertices);
	EBO EBO(indices);
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex3), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex3), (void*)(1 * sizeof(glm::vec3)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex3), (void*)(2 * sizeof(glm::vec3)));
	// Passes transformations matrix vector as 4 vec4s
	passTransformMatrix(instanceTransformMatrix, instance);
	// Unbind all to prevent accidentally modifying them
	VBO.Unbind();
	EBO.Unbind();
}

void CubeMesh::passTransformMatrix(std::vector <glm::mat4> instanceTransformMatrix, GLuint instance) {
	instances = instance;
	instancesTransformMatrix = instanceTransformMatrix;
	VAO.Bind();
	VBO instanceVBO(instancesTransformMatrix);
	VAO.LinkAttrib(instanceVBO, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(0));
	VAO.LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
	VAO.LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	VAO.LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	// Advances the pivot(?) in vertex shader
	// ie makes it use the next element in transform matrix after drawing an instance
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	VAO.Unbind();
	instanceVBO.Unbind();
}

void CubeMesh::DrawInstanced( Player& camera, GLFWwindow* window)
{
	// Bind shader to be able to access uniforms
	_mShader->Activate();
	VAO.Bind();


	glUniform3f(glGetUniformLocation(_mShader->getID(), "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	camera.Matrix(*_mShader, "camMatrix");
	glDrawElementsInstanced(mode, indices.size(), GL_UNSIGNED_INT, 0, instances);
	
}
void CubeMesh::Draw(Player& camera, GLFWwindow* window)
{
	// Bind shader to be able to access uniforms
	_mShader->Activate();
	VAO.Bind();


	glUniform3f(glGetUniformLocation(_mShader->getID(), "camPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	camera.Matrix(*_mShader, "camMatrix");
	glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);
}

GLenum CubeMesh::getMode()
{
	return mode;
}
GLuint CubeMesh::getInstances()
{
	return instances;
}
bool CubeMesh::isActivef()
{
	return isActive;
}
void CubeMesh::setMode(GLenum mode)
{
	this->mode = mode;
}

void CubeMesh::setInstances(GLuint instances)
{
	this->instances = instances;
}

void CubeMesh::setActive(bool active)
{
	isActive = active;
}
