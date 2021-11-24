![alt text](https://yt3.ggpht.com/ytc/AKedOLSQvjKGIF-QWrv9fOuUKHzTPdOY_83WCK-fl1Hn=s900-c-k-c0x00ffffff-no-rj)

# Voxel-Game-Demo
 A Minecraft like game with basic rendering, movement, block placement.. All made from scratch
 
 Downlod Pre-compiled binaries [Here](https://github.com/aaron-nuy/Voxel-Game-Demo/releases/tag/v0.1.0-alpha).
 
 Block textures can be changed by directly editing the texture atlas located in resources\textures\block, the size of the final texture atlas doesn't matter as long as it's a square with a length that is a power of 2.
 
# Build Instructions
 ### Windows
  Need to have CMake 3.10 installed and C++17 support<br/>
  Run build.bat and after it finishes binaries will be found in build/bin/Release and Visual Studio solution is two levels higher
  
  
 ### Linux
  There is no Linux support, and with the included libraries as they are, it won't compile.
  
  The .exe does run on Wine however
 
 
# TODO
 -Fix bug: surrounding chunks don't update when placing a block on edge of a chunk
 
 
  -Fix bug: inconsistent physics with variable framerate
  
 
 -Organize code and add comments
 
 
 -Add multithreading for world generation
 
 
 -Make it so movement doesn't completely stop when colliding with the world but slighty move to the side
 
 
 -Add dynamic world loading from hard drive
 
 
 

