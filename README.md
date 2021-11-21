![alt text](https://yt3.ggpht.com/ytc/AKedOLSQvjKGIF-QWrv9fOuUKHzTPdOY_83WCK-fl1Hn=s900-c-k-c0x00ffffff-no-rj)

# Voxel-Game-Demo
 A Minecraft like game with basic rendering, movement, block placement.. All made from scratch
 
 Downlod Pre-compiled binaries (executable) [Here](https://github.com/aaron-nuy/Voxel-Game-Demo/releases/tag/v0.1.0-alpha).
 
 Block textures can be changed by directly editing the texture atlas located in resources\textures\block, the size of the final texture atlas doesn't matter as long as it's a square with a length that is a power of 2.
 
# Build Instructions
 Good luck, you'll need it.
 
 Might publish build instructions in the future but I'm currently using Visual Studio to build it and it works fine. So..
 
 
# TODO
 -Organize code and add comments
 
 
 -Add multithreading for world generation
 
 
 -Add dynamic world loading from hard drive
 
 
 -Fix bug where speed decreases when looking down or up (due to orientation vector normalization)
 
 
 -Make it so movement doesn't completly stop when colliding with the world but slighty move to the side
 
 
 -Fix bug where surrounding chunks don't update when placing block on edge of chunk
