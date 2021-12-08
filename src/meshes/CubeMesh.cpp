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

CubeMesh::CubeMesh(Texture3D* text, Shader* shader) {
	_mShader = shader;
	_mTexture = text;
	_mVAO.Bind();
	VBO _mVBO(skyVertices, sizeof(skyVertices));
	EBO _mEBO(skyIndices, sizeof(skyIndices));
	_mVAO.LinkAttrib(_mVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
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

void CubeMesh::Draw(Player& camera, GLFWwindow* window,float aspectRatio)
{	// Bind shader to be able to access uniforms
	_mShader->Activate();
	_mVAO.Bind();

	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "skybox");

		glDepthFunc(GL_LEQUAL);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.getPosition(), camera.getPosition() + camera.getOrientation(), camera.UpVector())));
		projection = glm::perspective(glm::radians(70.0f), aspectRatio, 0.01f, 10009.0f);

		_mShader->SetUniform(_mShader->GetUniID("view"), view);
		_mShader->SetUniform(_mShader->GetUniID("projection"), projection);

		glDrawElements(GL_TRIANGLES, sizeof(skyIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glDepthFunc(GL_LESS);
	}
}

void CubeMesh::setMode(GLenum mode)
{
	this->mode = mode;
}

