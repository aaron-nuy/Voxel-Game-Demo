#pragma once
#include<thread>
#include"meshes/Model.h"
#include"meshes/Mesh.h"
#include"meshes/CubeMesh.h"
#include"world/ChunkManager.h"
#include"controls/MovementManager.h"
#include"abstractions/Polygone.h"
#include"abstractions/Texture3D.h"

#define LOG(x) std::cout << x << std::endl;

int windowWidth = 720, windowHeight = 720;
float freq = 0.00824f;
float depth = 64.0f;
const glm::vec3 skyColor = glm::vec3(3*0.221, 3*0.268, 3*0.298);
const float loadRatio = ChunkManager::_mRenderingDistance * Chunk::_mChunkSize/4;
bool isWindowed = 1;

// Key callback for GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
	}

}

void switchScreenMode(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (isWindowed) {
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(),0,0,mode->width,mode->height,GLFW_DONT_CARE );
			isWindowed = 0;
		}
		else {
			glfwSetWindowMonitor(window, NULL, 100, 100, 540, 540, GLFW_DONT_CARE);
			isWindowed = 1;
		}
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
	std::string skyboxFaces[6] = {
	"resources/textures/sky/right.jpg",
	"resources/textures/sky/left.jpg",
	"resources/textures/sky/top.jpg",
	"resources/textures/sky/bottom.jpg",
	"resources/textures/sky/front.jpg",
	"resources/textures/sky/back.jpg"
	};
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
	Shader* skyboxShader = new Shader("resources/shaders/skybox.vert", "resources/shaders/skybox.frag");
	// Creates a texture object
	Texture* dirt = new Texture("resources/textures/block/atlas.png", "diffuse", 0);
	Texture3D* skyboxTexture = new Texture3D(skyboxFaces);
	CubeMesh* skybox = new CubeMesh(skyboxTexture,skyboxShader);
	
	// Lightbulb mesh and its parameters
	glm::vec4 lightColor = glm::vec4(1.5f, 1.5f, 1.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(20.0f, 50.0f, 30.0f);
	// Chunkmanager, Player, Movement Manager 
	ChunkManager* chunkManager = new ChunkManager(chunkShader, dirt, freq, depth, 0.0f, 0.0f);
	Player* player = new Player( glm::vec3(chunkManager->getRenderDistance() * Chunk::_mChunkSize / 2,
								 Chunk::_mChunkSizeY/4,
								 chunkManager->getRenderDistance() * Chunk::_mChunkSize / 2)	);
	MovementManager* movementManager = new MovementManager(player, chunkManager,window);
	Polygone* crosshair = new Polygone(polygoneShader,0.005f,4);
	// Passes uniforms to shaders
	#pragma region MyRegion
	// Activates shader and sets its world location with the cube color and position
	chunkShader->Activate();
	chunkShader->SetUniform(chunkShader->GetUniID("skyColor"), skyColor.x, skyColor.y, skyColor.z);
	chunkShader->SetUniform(chunkShader->GetUniID("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	chunkShader->SetUniform(chunkShader->GetUniID("lightPos"), lightPos.x, lightPos.y, lightPos.z);
	skyboxShader->Activate();
	skyboxShader->SetUniform(skyboxShader->GetUniID("skyColor"), skyColor.x, skyColor.y, skyColor.z);
	#pragma endregion
	// OpenGl settings
	#pragma region MyRegion
	// Enables depth testing so no clipping between textures
	glEnable(GL_DEPTH_TEST);
	// Enables faceculling so that non visible fragments don't get calculated
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glEnable(GL_LINE_SMOOTH);
	#pragma endregion


	double time = glfwGetTime();
	float aspectRatio = windowWidth / (float)windowHeight;
	std::string windowTitle;
	glm::vec3 previousPlayerPosition = player->getPosition();
	while (!glfwWindowShouldClose(window) && !(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)) {
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
		player->UpdateMatrix(70.0f, aspectRatio, 0.01f, 500.0f); // Updates projection matrix
		chunkManager->Draw(*player, window);
		crosshair->Draw(vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.5f,0.5f), 0, 1.f, aspectRatio);
		// Movement
		movementManager->ManageMovement();
		// skybox
		skybox->Draw(*player,window, aspectRatio);

		//	Misc tasks
		#pragma region MyRegion
			// Refresh screen
			glfwSwapBuffers(window);
			//	Handles window resizing and stuff
			glfwGetWindowSize(window, &windowWidth, &windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);
			aspectRatio = windowWidth / (float)windowHeight;
			glfwSetKeyCallback(window, switchScreenMode);
			glfwSwapInterval(1);
			glfwPollEvents();
			// Changes title
			windowTitle = "Clone - X:" + std::to_string((int)player->getPosition().x) + " Y:" + std::to_string((int)player->getPosition().y) + " Z:" + std::to_string((int)player->getPosition().z);
			glfwSetWindowTitle(window, windowTitle.c_str());
			#pragma endregion
	}

	// Destroys windows and ends program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}



