#include "Polygone.h"



Polygone::Polygone(Shader* shader,GLfloat radius, GLfloat numberOfSides)
{	
/*!
* Initializes a polygone of size n>3
*	shader  : A pointer to the polygone shader object
*	radius  : The radius of the plygone relative to the window size 0<r<=1
*	numberOfSides : How many sides should the polygone have, best to be n>3
*/
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

void Polygone::Draw(glm::vec4 color, glm::vec2 position,GLfloat angle, GLfloat scale, GLfloat aspectRatio) {

	transform = glm::translate(glm::mat4(1.0f), glm::vec3((position.x*2)-1, (position.y*2)-1, 0.1f));
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

	_mShader->Activate();
	_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
	_mShader->SetUniform(_mShader->GetUniID("rotation"), rotation);
	_mShader->SetUniform(_mShader->GetUniID("color"), color);
	_mShader->SetUniform(_mShader->GetUniID("scale"), scale);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	

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


	_mVAO.Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
}
