#include "Polygone.h"


/*!
 Initializes a polygone of size n>3
	shader  : A pointer to the polygone shader object
	radius  : The radius of the plygone relative to the window size 0<r<=1
	numberOfSides : How many sides should the polygone have, best to be n>3
*/
Polygone::Polygone(Shader* shader,GLfloat radius, GLfloat numberOfSides)
{	

	_mShader = shader;
	std::vector<GLfloat> vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(-radius*2.0f);
	vertices.push_back(0.0f);

	GLfloat Angle = -glm::radians(360.0f) / numberOfSides;

	float previousX;
	float previousY;
	for (unsigned short i = 0; i < numberOfSides; i++) {
		previousX = vertices[vertices.size() - 2];
		previousY = vertices[vertices.size() - 1];
		vertices.push_back( previousX * cos(Angle) - previousY * sin(Angle));
		vertices.push_back( previousX * sin(Angle) + previousY * cos(Angle));
	}

	_mVAO.Bind();
	_mVBO.Bind();
	_mVBO.Load(vertices);
	_mVAO.LinkAttrib(_mVBO, 0, 2, GL_FLOAT, sizeof(GLfloat)*2, (void*)0);
	_mVAO.Unbind();
	_mVBO.Unbind();

	numberOfVertices = vertices.size() / 2;
}


/*
 Initializes a polygone of size n>3
	shader  : A pointer to the polygone shader object
	radius  : The radius of the plygone relative to the window size 0<r<=1
	numberOfSides : How many sides should the polygone have, best to be n>3
*/
Polygone::Polygone(Shader* shader, Texture* texture, GLfloat radius, GLfloat numberOfSides)
{

	_mTexture = texture;
	_mShader = shader;
	std::vector<GLfloat> vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	vertices.push_back(-radius * 2.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.5f);



	for (unsigned short i = 0; i < numberOfSides; i++) {
		GLfloat Angle = -(glm::radians(360.0f) / numberOfSides)*(i+1);
		vertices.push_back(vertices[4] * cos(Angle) - vertices[5] * sin(Angle));
		vertices.push_back(vertices[4] * sin(Angle) + vertices[5] * cos(Angle));

		vertices.push_back((vertices[6]-0.5f) * cos(Angle) - (vertices[7]-0.5f) * sin(Angle) + 0.5f);
		vertices.push_back((vertices[6]-0.5f) * sin(Angle) + (vertices[7]-0.5f) * cos(Angle) + 0.5f);
	}

	_mVAO.Bind();
	_mVBO.Bind();
	_mVBO.Load(vertices);
	_mVAO.LinkAttrib(_mVBO, 0, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)(0 * sizeof(GLfloat)));
	_mVAO.LinkAttrib(_mVBO, 1, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)(2 * sizeof(GLfloat)));
	_mVAO.Unbind();
	_mVBO.Unbind();

	numberOfVertices = vertices.size() / 4;
}

void Polygone::Draw(glm::vec4 color, glm::vec2 position,GLfloat angle, GLfloat scale, GLfloat aspectRatio) {
	GLfloat a = angle - 360*((int)angle / 360);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3((position.x*2)-1, (position.y*2)-1, 0.1f));
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(a), glm::vec3(0.0f, 0.0f, 1.0f));

	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
	_mShader->SetUniform(_mShader->GetUniID("rotation"), rotation);
	_mShader->SetUniform(_mShader->GetUniID("color"), color);
	_mShader->SetUniform(_mShader->GetUniID("scale"), scale);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	_mShader->SetUniform(_mShader->GetUniID("isTextured"), int(_mTexture != NULL));

	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", 1);
	}

	_mVAO.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
}


void Polygone::Draw(glm::vec2 position, GLfloat angle, GLfloat scale, GLfloat aspectRatio) {
	GLfloat a = angle - 360 * ((int)angle / 360);
	transform = glm::translate(glm::mat4(1.0f), glm::vec3((position.x * 2) - 1, (position.y * 2) - 1, 0.1f));
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(a), glm::vec3(0.0f, 0.0f, 1.0f));

	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
	_mShader->SetUniform(_mShader->GetUniID("rotation"), rotation);
	_mShader->SetUniform(_mShader->GetUniID("color"), color);
	_mShader->SetUniform(_mShader->GetUniID("scale"), scale);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	_mShader->SetUniform(_mShader->GetUniID("isTextured"), int(_mTexture != NULL));

	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", 1);
	}

	_mVAO.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
}

void Polygone::Draw(glm::vec2 position, GLfloat aspectRatio)
{
	transform = glm::translate(glm::mat4(1.0f), glm::vec3((position.x * 2) - 1, (position.y * 2) - 1, 0.1f));

	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
	_mShader->SetUniform(_mShader->GetUniID("rotation"), rotation);
	_mShader->SetUniform(_mShader->GetUniID("color"), color);
	_mShader->SetUniform(_mShader->GetUniID("scale"), scale);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	_mShader->SetUniform(_mShader->GetUniID("isTextured"), int(_mTexture != NULL));

	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", 1);
	}

	_mVAO.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
}


void Polygone::Draw(GLfloat aspectRatio) {

	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
	_mShader->SetUniform(_mShader->GetUniID("rotation"), rotation);
	_mShader->SetUniform(_mShader->GetUniID("color"), color);
	_mShader->SetUniform(_mShader->GetUniID("scale"), scale);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	_mShader->SetUniform(_mShader->GetUniID("isTextured"), int(_mTexture != NULL));

	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", 1);
	}

	_mVAO.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
}
