#include "CubeMesh.h"

CubeMesh::CubeMesh() {
	_mShader = new Shader("resources/shaders/cube.vert", "resources/shaders/cube.frag");
	_mVAO.Bind();
	VBO _mVBO(vertices, sizeof(vertices));
	EBO _mEBO(indices, sizeof(indices));
	_mVAO.LinkAttrib(_mVBO, 0, 3, GL_FLOAT, 3*sizeof(GLfloat), (void*)0);
	_mVAO.Unbind();
	_mVBO.Unbind();
	_mEBO.Unbind();
};



void CubeMesh::passTransformMatrix(glm::mat4 instanceTransformMatrix) {
	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), instanceTransformMatrix);
}

void CubeMesh::Draw(Player& camera, GLFWwindow* window)
{	// Bind shader to be able to access uniforms
	_mShader->Activate();
	_mVAO.Bind();

	camera.Matrix(*_mShader, "camMatrix");
	glDrawElements(mode, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void CubeMesh::setMode(GLenum mode)
{
	this->mode = mode;
}

