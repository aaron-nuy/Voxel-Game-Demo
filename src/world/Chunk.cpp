#include "Chunk.h"

Chunk::Chunk( GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos) {
	posX = xPos;
	posZ = zPos;
	this->generateTerrain(freq, depth, posX, posZ);

}

// Checks if Vertices should be rendered and constructs chunk
// Outdated: no chunk borders optimizing
void Chunk::checkFaces() {
	GLuint Indice = 0;
	std::vector<Vertex3> Face;
	GLuint indice0;
	GLuint indice1;
	GLuint indice2;
	GLuint indice3;
	Indices.clear();
	Vertices.clear();
	for (unsigned short x = 0; x < _mChunkSize; x++) {
		for (unsigned short z = 0; z < _mChunkSize; z++) {
			for (unsigned short y = 0; y < _mChunkSizeY; y++) {
				if (!Blocks[x][y][z] == 0) {
					if ( (y == 0) || (Blocks[x][y - 1][z] == c_Air)) { // Checks Bottom Side 
						Face = Bottom;
						switch (Blocks[x][y][z]) {
						case 2:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case 3:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
					if ((x==0) || (Blocks[x - 1][y][z] == c_Air)) { // Checks Left Side
						Face = Left;
						switch (Blocks[x][y][z]) {
						case 2:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case 3:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
					if ((z == 0) || (Blocks[x][y][z - 1] == c_Air)) { // Checks Back Side
						Face = Back;
						switch (Blocks[x][y][z]) {
						case 2:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case 3:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
					if ((x==_mChunkSize-1) || (Blocks[x + 1][y][z] == c_Air)) { // Checks Right Side
						Face = Right;
						switch (Blocks[x][y][z]) {
						case 2:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case 3:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
					if ((y == _mChunkSizeY - 1) || (Blocks[x][y + 1][z] == c_Air)) { // Checks Top Side
						Face = Top;
						switch (Blocks[x][y][z]) {
						case 2:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case 3:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
					if ((z == _mChunkSize - 1) || (Blocks[x][y][z + 1] == c_Air)) { // Checks Front Side
						Face = Front;
						switch (Blocks[x][y][z]) {
						case c_Stone:
							Face[0].texUVs = glm::vec2(0.5f, 0.0f);
							Face[1].texUVs = glm::vec2(1.0f, 0.0f);
							Face[2].texUVs = glm::vec2(1.0f, 0.5f);
							Face[3].texUVs = glm::vec2(0.5f, 0.5f);
							break;
						case c_Dirt:
							Face[0].texUVs = glm::vec2(0.5f, 0.5f);
							Face[1].texUVs = glm::vec2(1.0f, 0.5f);
							Face[2].texUVs = glm::vec2(1.0f, 1.0f);
							Face[3].texUVs = glm::vec2(0.5f, 1.0f);
							break;
						}
						Face[0].position += glm::vec3(x, y, z);
						Face[1].position += glm::vec3(x, y, z);
						Face[2].position += glm::vec3(x, y, z);
						Face[3].position += glm::vec3(x, y, z);
						Vertices.push_back(Face[0]);
						Vertices.push_back(Face[1]);
						Vertices.push_back(Face[2]);
						Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						Indices.push_back(indice0);
						Indices.push_back(indice1);
						Indices.push_back(indice2);
						Indices.push_back(indice2);
						Indices.push_back(indice3);
						Indices.push_back(indice0);
					}
				}
			}
		}
	}

}

// Pushes mesh data to vao
void Chunk::loadVertices() {
	_mVAO.Bind();
	_mVBO.Load(Vertices);
	_mEBO.Load(Indices);
	_mVAO.LinkAttrib(_mVBO, 0, 3, GL_FLOAT, sizeof(Vertex3), (void*)0);
	_mVAO.LinkAttrib(_mVBO, 1, 3, GL_FLOAT, sizeof(Vertex3), (void*)(1 * sizeof(glm::vec3)));
	_mVAO.LinkAttrib(_mVBO, 2, 2, GL_FLOAT, sizeof(Vertex3), (void*)(2 * sizeof(glm::vec3)));
	_mVAO.Unbind();
	_mVBO.Unbind();
	_mEBO.Unbind();
}

// Noise Generation
void Chunk::generateTerrain(GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos) {
	// Noise generation
	float height;
	float xP;
	float zP;
	for (unsigned char x = 0; x < _mChunkSize; x++) {
		for (unsigned char z = 0; z < _mChunkSize; z++) {
			xP = x + xPos;
			zP = z + zPos;
			height = glm::simplex(glm::vec2(xP * freq, zP * freq));		
			height = ((height + 1) / 2.0f) * (depth*2);
			height += glm::perlin(glm::vec2(xP *10000-963, zP *10000-142))*70;
			if (height >= _mChunkSizeY || isnan(height)) {
				height = _mChunkSizeY - 1;
			}
			Blocks[x][(int)height][z] = c_Grass;
			for (unsigned char y = 0; y < std::max(2.5f,height/3); y++) {
				Blocks[x][y][z] = c_Stone;
			}
			for (unsigned char y = std::max(2.5f, height / 3); y < height-1; y++) {
				Blocks[x][y][z] = c_Dirt;
			}
		}
	}
}

// Destructor 
// Deletes VBO/EBO/VAO to save gpu memory
Chunk::~Chunk()
{
	_mVBO.Delete();
	_mEBO.Delete();
	_mVAO.Delete();
}

