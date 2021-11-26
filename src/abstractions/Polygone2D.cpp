#include "Polygone2D.h"

Polygone2D::Polygone2D(Texture* text, Shader* shade )
{
	texture = text;
	shader = shade;
	VAO.Bind();
	VBO.Load(crossHairArrayVerts, sizeof(crossHairArrayVerts));
	EBO.Load(crossHairArrayIndices, sizeof(crossHairArrayIndices));
	VAO.LinkAttrib(VBO, 0, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)0);
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)(2 * sizeof(GLfloat)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Polygone2D::Draw(float aspect) {
	shader->Activate();

	texture->Bind();
	texture->Assign(*shader, "diffuse0", 1);

	VAO.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}