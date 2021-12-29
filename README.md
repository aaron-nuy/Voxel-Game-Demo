![alt text](https://i.imgur.com/XNCulVE.png)

# Voxel-Game-Demo
 A Minecraft like game with basic rendering, movement, block placement.. All made from scratch  
 The code is a disastrous mess and is anything but elegant, yet it works well enough and isn't terribly unreadable
   
 This project was just a challenge I made for myself while also a way to learn graphics programminng on the side, so manage expectation..
   
     
 As of 29/12/2021 I don't believe that I'll ever continue to work on this in the future, though there is a lot of work that still needs to be done
   
   
 Solution file for VS22 is included
 
 Downlod Pre-compiled binaries (executable) [Here](https://github.com/aaron-nuy/Voxel-Game-Demo/releases/tag/v0.3.0_Alpha).
 
 Block textures can be changed by directly editing the texture atlas located in resources\textures\block, the size of the final texture atlas doesn't matter as long as it's a square with a length that is a power of 2.
 
 
# Controls  
 Toggle Collision : U  
 Toggle Fullscreen : F  
 ## Normal Mode  
  Movemnt : ZQSD  
  Jump : Space  
  Shift : Sprint  
  Place Block : Left Mouse  
  Destroy Block : Right Mouse  
 ## Freecam Mode  
  Movemnt : ZQSD  
  Fly Up : Space  
  Fly Down : Control  
  Speed Up : Shift  
  
 
 
# Build Instructions
 ### Windows
  ~~Need to have CMake 3.10 installed and C++17 support<br/>
  Run build.bat and after it finishes binaries will be found in build/bin/Release and Visual Studio solution is two levels higher~~  
  Build file doesn't work with the latest version. Needs to be updated

 
# TODO
 -Add feature: surrounding chunks don't update when placing a block on the edge of a chunk
  
 
 -Organize code and add comments
 
 
 -Add multithreading for world generation
 
 
 -Make it so movement doesn't completely stop when colliding with the world but slighty move to the side
 
 
 -Add dynamic world loading from hard drive
 
 
 

