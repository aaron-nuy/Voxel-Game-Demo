cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set the project name
project(Voxel-Game-Demo VERSION 0.1.0)

# add the executable
add_executable(Voxel-Game-Demo
					 src/abstractions/ShaderClass.cpp
					 src/abstractions/EBO.cpp
					 src/abstractions/VBO.cpp
					 src/abstractions/VAO.cpp
					 src/abstractions/Texture.cpp
					 src/abstractions/Polygone2D.cpp
					 src/controls/Player.cpp
					 src/controls/MovementManager.cpp
					 src/world/Chunk.cpp
					 src/world/ChunkManager.cpp
					 src/dependencies/stb_image.cpp
					 src/dependencies/glad.cpp
					 src/Main.cpp)


target_include_directories(Voxel-Game-Demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/include/)
target_link_libraries(Voxel-Game-Demo ${CMAKE_SOURCE_DIR}/Libraries/lib/glfw3.lib)

