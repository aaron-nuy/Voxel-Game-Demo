#include "Polygone2D.h"

Polygone2D::Polygone2D(Texture* text, Shader* shade )
{
	texture = text;
	shader = shade;
	_mVAO.Bind();
	_mVBO.Load(crossHairArrayVerts, sizeof(crossHairArrayVerts));
	_mVEBO.Load(crossHairArrayIndices, sizeof(crossHairArrayIndices));
	_mVVAO.LinkAttrib(_mVVBO, 0, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)0);
	_mVVAO.LinkAttrib(_mVVBO, 1, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)(2 * sizeof(GLfloat)));
	_mVVAO.Unbind();
	_mVVBO.Unbind();
	_mVEBO.Unbind();
}

void Polygone2D::Draw(float aspect) {
	shader->Activate();

	texture->Bind();
	texture->Assign(*shader, "diffuse0", 1);

	_mVVAO.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
