#include "ChunkManager.h"

int modulo(float Pos, int mod) {
	return (((int)floor(Pos) % mod) + mod) % mod;
}

ChunkManager::ChunkManager(Shader* shader, Texture* text, GLfloat freq, GLfloat depth, GLfloat xPos, GLfloat zPos) {
	_mTexture = text;
	_mShader = shader; 


	// Initialize chunks and stores them in 2D vector
	std::vector<std::shared_ptr<Chunk>> chunkVector;
	for (unsigned short x = 0; x < _mRenderingDistance; x++) {
		chunkVector.clear();
		for (unsigned short z = 0; z < _mRenderingDistance; z++) {
			chunkVector.push_back(std::make_shared<Chunk>(freq, depth, xPos+x*Chunk::_mChunkSize, zPos+z* Chunk::_mChunkSize));
		}
		chunkList.push_back(chunkVector);
	}
	manageChunks();
}

/*
	Functions for loading new chunks in 4 directions
		Deletes the last row chunk in opposite direction of generation 
		Generates new row of chunks in desired direction
		Pushes new row into chunkList
		Manages certain rows so chunk borders don't get rendered
*/
void ChunkManager::GenerateX(GLfloat freq, GLfloat depth) {
	chunkList.erase(chunkList.begin());
	std::vector<std::shared_ptr<Chunk>> chunkVector;
	for (unsigned short x = 0; x < _mRenderingDistance; x++) {
		chunkVector.push_back(std::make_shared<Chunk>(freq, depth, chunkList[_mRenderingDistance-2][0]->posX + Chunk::_mChunkSize, chunkList[0][0]->posZ + x*Chunk::_mChunkSize));
	}
	chunkList.push_back(chunkVector);
	for (unsigned short x = 0; x < _mRenderingDistance; x++) {
		manageChunk(0,x);
		manageChunk(_mRenderingDistance - 1,x);
		manageChunk(_mRenderingDistance - 2,x);
	}
}
void ChunkManager::GenerateZ(GLfloat freq, GLfloat depth) {
	for (unsigned short z = 0; z < _mRenderingDistance; z++) {
		chunkList[z].erase(chunkList[z].begin());
		chunkList[z].push_back(std::make_shared<Chunk>(freq, depth, chunkList[0][0]->posX + z * Chunk::_mChunkSize, chunkList[0][_mRenderingDistance - 2]->posZ + Chunk::_mChunkSize));
	}
	for (unsigned short z = 0; z < _mRenderingDistance; z++) {
		manageChunk(z, 0);
		manageChunk(z, _mRenderingDistance - 1);
		manageChunk(z, _mRenderingDistance - 2);
	}
}
void ChunkManager::GenerateMX(GLfloat freq, GLfloat depth) {
	chunkList.erase(chunkList.end()-1);
	std::vector<std::shared_ptr<Chunk>> chunkVector;
	for (unsigned short x = 0; x < _mRenderingDistance; x++) {
		chunkVector.push_back(std::make_shared<Chunk>(freq, depth, chunkList[0][0]->posX - Chunk::_mChunkSize, chunkList[0][0]->posZ + x * Chunk::_mChunkSize));
	}
	chunkList.insert(chunkList.begin(), chunkVector);
	for (unsigned short x = 0; x < _mRenderingDistance; x++) {
		manageChunk(_mRenderingDistance-1, x);
		manageChunk(0, x);
		manageChunk(1, x);
	}
}


void ChunkManager::GenerateMZ(GLfloat freq, GLfloat depth) {
	for (unsigned short z = 0; z < _mRenderingDistance; z++) {
		chunkList[z].erase(chunkList[z].end() - 1);
		chunkList[z].insert(chunkList[z].begin(), std::make_shared<Chunk>(freq, depth, chunkList[0][0]->posX + z * Chunk::_mChunkSize, chunkList[z][0]->posZ - Chunk::_mChunkSize));
	}
	for (unsigned short z = 0; z < _mRenderingDistance; z++) {
		manageChunk(z, _mRenderingDistance - 1);
		manageChunk(z, 0);
		manageChunk(z, 1);
	}
}

// Returns block data corresponding to position in the wolrd
unsigned char ChunkManager::getBlock(glm::vec3 position)
{
	glm::vec3 PIC = getPositionInChunk(position);
	glm::vec3 CC = getCurrentChunk(position);
	return chunkList[CC.x][CC.z]->Blocks[(int)PIC.x][(int)PIC.y][(int)PIC.z];
}



void ChunkManager::setBlock(glm::vec3 position, Block block)
{
	glm::vec3 PIC = getPositionInChunk(position);
	glm::vec3 CC = getCurrentChunk(position);
	chunkList[CC.x][CC.z]->Blocks[(int)PIC.x][(int)PIC.y][(int)PIC.z] = block;
	manageChunk(CC.x, CC.z);	
}

bool ChunkManager::isInBoundaries(glm::vec3 position) {
	glm::vec3 PIC = getPositionInChunk(position);
	glm::vec3 CC = getCurrentChunk(position);

	if (PIC.y < 0 || PIC.y >= Chunk::_mChunkSizeY) {
		return false;
	}
	else if (	 (CC.x < 0 || CC.x >= _mRenderingDistance)
			||   (CC.z < 0 || CC.z >= _mRenderingDistance)) {
		return false;
	}
	return true;
}

// Returns which chunk a set of coordinates correspond to
glm::vec3 ChunkManager::getCurrentChunk(glm::vec3 Pos) {
	return glm::vec3(((int)floor(Pos.x) - chunkList[0][0]->posX) / Chunk::_mChunkSize, 0, ((int)floor(Pos.z) - chunkList[0][0]->posZ) / Chunk::_mChunkSize);

}
// Returns the block in chunk that a set of coordinates correspond to
glm::vec3 ChunkManager::getPositionInChunk(glm::vec3 Pos) {
	return glm::vec3(modulo(Pos.x, Chunk::_mChunkSize), (int)Pos.y, modulo(Pos.z, Chunk::_mChunkSize));
}

// Transforms chunk to world coordinates and renders it
void ChunkManager::Draw(Player& player, GLFWwindow* window) {
	_mShader->Activate();
	if (_mTexture != NULL) {
		_mTexture->Bind();
		_mTexture->Assign(*_mShader, "diffuse0", _mTexture->getUnit());
	}

	for (unsigned short i = 0; i < _mRenderingDistance; i++) {
		for (unsigned short j = 0; j < _mRenderingDistance; j++) {
			chunkList[i][j]->_mVAO.Bind();
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(chunkList[i][j]->posX, 0, chunkList[i][j]->posZ));
			_mShader->SetUniform(_mShader->GetUniID("transform"), transform);
			_mShader->SetUniform(_mShader->GetUniID("camPos"), player.getPosition().x, player.getPosition().y, player.getPosition().z);
			player.Matrix(*_mShader, "camMatrix");
			glDrawElements(GL_TRIANGLES, chunkList[i][j]->Indices.size(), GL_UNSIGNED_INT, 0);
		}
	}
}


/*
	VERY EXPENSIVE ON PERFORMANCE, MUST OPTIMIZE
		For each block face in chunk checks if it should be rendered
		if so, it pushes it and its indices to chunk's indices and vertices lists
*/
void ChunkManager::manageChunk(int i, int j) {
	GLuint Indice = 0;
	std::vector<Vertex3> Face;
	GLuint indice0;
	GLuint indice1;
	GLuint indice2;
	GLuint indice3;
	chunkList[i][j]->Vertices.clear();
	chunkList[i][j]->Indices.clear();
	for (unsigned short x = 0; x < Chunk::_mChunkSize; x++) {
		for (unsigned short z = 0; z < Chunk::_mChunkSize; z++) {
			for (unsigned short y = 0; y < Chunk::_mChunkSizeY; y++) {
				if (!chunkList[i][j]->Blocks[x][y][z] == 0) {
					if ((y == 0) || (chunkList[i][j]->Blocks[x][y - 1][z] == c_Air)) { // Checks Bottom Side 
						Face = Bottom;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
					if ((y == Chunk::_mChunkSizeY - 1) || (chunkList[i][j]->Blocks[x][y + 1][z] == c_Air)) { // Checks Top Side
						Face = Top;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
					if ((i == 0 && x == 0) || (x > 0 && chunkList[i][j]->Blocks[x - 1][y][z] == c_Air) || (x == 0 && chunkList[i - 1][j]->Blocks[Chunk::_mChunkSize - 1][y][z] == c_Air)) { // Checks Left Side
						Face = Left;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
					if ((j == 0 && z == 0) || (z > 0 && chunkList[i][j]->Blocks[x][y][z - 1] == c_Air) || (z == 0 && chunkList[i][j - 1]->Blocks[x][y][Chunk::_mChunkSize - 1] == c_Air)) { // Checks Back Side
						Face = Back;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
					if ((i == _mRenderingDistance - 1 && x == Chunk::_mChunkSize - 1) || (x < Chunk::_mChunkSize - 1 && chunkList[i][j]->Blocks[x + 1][y][z] == c_Air) || (x == Chunk::_mChunkSize - 1 && chunkList[i + 1][j]->Blocks[0][y][z] == c_Air)) { // Checks Right Side
						Face = Right;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
					if ((j == _mRenderingDistance - 1 && z == Chunk::_mChunkSize - 1) || (z < Chunk::_mChunkSize - 1 && chunkList[i][j]->Blocks[x][y][z + 1] == c_Air) || (z == Chunk::_mChunkSize - 1 && chunkList[i][j + 1]->Blocks[x][y][0] == c_Air)) { // Checks Front Side
						Face = Front;
						switch (chunkList[i][j]->Blocks[x][y][z]) {
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
						chunkList[i][j]->Vertices.push_back(Face[0]);
						chunkList[i][j]->Vertices.push_back(Face[1]);
						chunkList[i][j]->Vertices.push_back(Face[2]);
						chunkList[i][j]->Vertices.push_back(Face[3]);
						indice0 = Indice++;
						indice1 = Indice++;
						indice2 = Indice++;
						indice3 = Indice++;
						chunkList[i][j]->Indices.push_back(indice0);
						chunkList[i][j]->Indices.push_back(indice1);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice2);
						chunkList[i][j]->Indices.push_back(indice3);
						chunkList[i][j]->Indices.push_back(indice0);
					}
				}
			}
		}
	}
	chunkList[i][j]->loadVertices();

};
void ChunkManager::manageChunks() {
	for (unsigned short i = 0; i < _mRenderingDistance; i++) {
		for (unsigned short j = 0; j < _mRenderingDistance; j++) {
			manageChunk(i, j);
		}
	}
}

unsigned char ChunkManager::getRenderDistance() {
	return _mRenderingDistance;
}
