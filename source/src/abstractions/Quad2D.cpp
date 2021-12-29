#include "Quad2D.h"

Quad2D::Quad2D(Shader* shader,Texture* texture,GLfloat size )
{
	GLfloat crossHairArrayVerts[16] = {
		-size/2, -size/2, 0.0f, 0.0f,
		-size/2,  size/2, 0.0f, 1.0f,
		 size/2,  size/2, 1.0f, 1.0f,
		 size/2, -size/2, 1.0f, 0.0f
	};
	_mTexture = texture;
	_mShader = shader;
	VAO.Bind();
	VBO.Load(crossHairArrayVerts, sizeof(crossHairArrayVerts));
	EBO.Load(crossHairArrayIndices, sizeof(crossHairArrayIndices));
	VAO.LinkAttrib(VBO, 0, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)0);
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(GLfloat) * 4, (void*)(2 * sizeof(GLfloat)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Quad2D::Draw(GLfloat aspectRatio) {
	_mShader->Activate();
	VAO.Bind();
	_mTexture->Bind();
	_mTexture->Assign(*_mShader, "diffuse0", 1);
	_mShader->SetUniform(_mShader->GetUniID("aspectRatio"), aspectRatio);
	_mShader->SetUniform(_mShader->GetUniID("transform"), aspectRatio);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}