#pragma once
#include<thread>
#include"meshes/Model.h"
#include"meshes/Mesh.h"
#include"meshes/CubeMesh.h"
#include"world/ChunkManager.h"
#include"controls/MovementManager.h"
#include"abstractions/Polygone.h"


int windowWidth = 720, windowHeight = 720;
const float FPS = 60;
float freq = 0.007f;
float depth = 32.0f;
const glm::vec3 skyColor = glm::vec3(0.90, 0.90f, 0.96f);
const float loadRatio = ChunkManager::_mRenderingDistance * Chunk::_mChunkSize/4;

// Key callback for GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
	}

}
// Generating terrain function for secondary thread
void generate(ChunkManager* chunkManager, Player* player, glm::vec3* previousPlayerPosition, float freq, float depth, GLFWwindow* window) {
	// Change OpenGl context to current thread
	glfwMakeContextCurrent(window);
	// If the player moves more than 64 blocks 
	// in a certain direction, generate terrain
	if (player->getPosition().x - previousPlayerPosition->x >= loadRatio) {
		for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
			chunkManager->GenerateX(freq, depth);
		}
		previousPlayerPosition->x = player->getPosition().x;
	}
	else if (player->getPosition().x - previousPlayerPosition->x <= -loadRatio) {
		for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
			chunkManager->GenerateMX(freq, depth);
		}
		previousPlayerPosition->x = player->getPosition().x;
	}
	if (player->getPosition().z - previousPlayerPosition->z >= loadRatio) {
		for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
			chunkManager->GenerateZ(freq, depth);
		}
		previousPlayerPosition->z = player->getPosition().z;
	}
	else if (player->getPosition().z - previousPlayerPosition->z <= -loadRatio) {
		for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
			chunkManager->GenerateMZ(freq, depth);
		}
		previousPlayerPosition->z = player->getPosition().z;
	}
	// Unhook OpenGl from second thread
	glfwMakeContextCurrent(NULL);
}


int main() {
	// Sets default settings and initializes window
	#pragma region MyRegion
	// Initialize GLFW
	glfwInit();
	// Set OpenGl version and  profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Initialize window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Clone", NULL, NULL);
	// Check if window creation is successful if not, terminate it
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}
	// Set the context to the window
	glfwMakeContextCurrent(window);
	//Load Glad
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);
	#pragma endregion
	// Initializes shaders for needed objects
	Shader* chunkShader = new Shader("resources/shaders/chunkshader.vert", "resources/shaders/chunkshader.frag");
	Shader* polygoneShader = new Shader("resources/shaders/polygone.vert", "resources/shaders/polygone.frag");
	// Creates a texture object
	Texture* dirt = new Texture("resources/textures/block/tex.png", "diffuse", 0);
	
	// Lightbulb mesh and its parameters
	glm::vec4 lightColor = glm::vec4(1.5f, 1.5f, 1.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(20.0f, 50.0f, 30.0f);
	// Chunkmanager, Player, Movement Manager 
	ChunkManager* chunkManager = new ChunkManager(chunkShader, dirt, freq, depth, 0.0f, 0.0f);
	Player* player = new Player( glm::vec3(chunkManager->getRenderDistance() * Chunk::_mChunkSize / 2,
								 Chunk::_mChunkSizeY,
								 chunkManager->getRenderDistance() * Chunk::_mChunkSize / 2)	);
	MovementManager* movementManager = new MovementManager(player, chunkManager,window);
	Polygone* crosshair = new Polygone(polygoneShader,0.003f,10);
	// Passes uniforms to shaders
	#pragma region MyRegion
	// Activates shader and sets its world location with the cube color and position
	chunkShader->Activate();
	chunkShader->SetUniform(chunkShader->GetUniID("skyColor"), skyColor.x, skyColor.y, skyColor.z);
	chunkShader->SetUniform(chunkShader->GetUniID("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	chunkShader->SetUniform(chunkShader->GetUniID("lightPos"), lightPos.x, lightPos.y, lightPos.z);
	#pragma endregion
	// OpenGl settings
	#pragma region MyRegion
	// Enables depth testing so no clipping between textures
	glEnable(GL_DEPTH_TEST);
	// Enables faceculling so that non visible fragments don't get calculated
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_LINE_SMOOTH);
	#pragma endregion



	double time = glfwGetTime();
	std::string windowTitle;
	glm::vec3 previousPlayerPosition = player->getPosition();
	while (!glfwWindowShouldClose(window) && !(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)) {
		if (glfwGetTime() - time >= 1/FPS) {
			// Time and clears screen
			#pragma region MyRegion
			time = glfwGetTime();
			glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			#pragma endregion
			// Generating terrain if player mmoves far enough
			if (player->getPosition().x - previousPlayerPosition.x >= loadRatio) {
				for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++){
					chunkManager->GenerateX(freq, depth);
				}
				previousPlayerPosition.x = player->getPosition().x;
			}
			else if (player->getPosition().x - previousPlayerPosition.x <= -loadRatio) {
				for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
					chunkManager->GenerateMX(freq, depth);
				}
				previousPlayerPosition.x = player->getPosition().x;
			}
			if (player->getPosition().z - previousPlayerPosition.z >= loadRatio) {
				for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
					chunkManager->GenerateZ(freq, depth);
				}
				previousPlayerPosition.z = player->getPosition().z;
			}
			else if (player->getPosition().z - previousPlayerPosition.z <= -loadRatio) {
				for (int i = 0; i < ChunkManager::_mRenderingDistance / 4.0f; i++) {
					chunkManager->GenerateMZ(freq, depth);
				}
				previousPlayerPosition.z = player->getPosition().z;
			}

			// Update view and projection matrices
			player->UpdateMatrix(90.0f, (float)windowWidth / windowHeight, 0.01f, 500.0f); // Updates projection matrix
			chunkManager->Draw(*player, window);
			crosshair->Draw(glm::vec2(0.0f), (float)windowWidth / windowHeight);
			// Movement
			movementManager->ManageMovement();

			//	Misc tasks
			#pragma region MyRegion
			// Refresh screen
			glfwSwapBuffers(window);
			//	Handles window resizing and stuff
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);
			glfwPollEvents();
			// Changes title
			windowTitle = "Clone - X:" + std::to_string((int)player->getPosition().x) + " Y:" + std::to_string((int)player->getPosition().y) + " Z:" + std::to_string((int)player->getPosition().z);
			glfwSetWindowTitle(window, windowTitle.c_str());
			#pragma endregion
		}
	}

	// Destroys windows and ends program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}



