# HeightmapDemo
## Description
HeightmapDemo is a small OpenGL application used for playing around with both OpenGL and simple procedural terrain generation similiar to Minecraft.
It generates a height map using two dimensional Perlin noise and uses that to position cubes in a small grid. While frequency of noise
is currently hardcoded, eventually this will be adjustable.
  
## Installation
Heightmap demo requires SFML and GLM. It also requires CMake to setup the visual studio solution file. It does not currently work on linux.

To install:

1. Open CMake gui and set the source code location to whichever directory the CMakeLists.txt file is located.
1. Set the build directory to somewhere convenient (such as <source-directory>/build).
1. Click the configure button.
1. Set GLM_INCLUDES, SFML_INCLUDES and SFML_LIBRARIES to where you placed the GML/SFML includes and libs.
1. Click generate. This will place the solution file in the build directory.

## Future additions
Currently HeightmapDemo is very simple. The plan is to improve memory allocation to avoid memory fragmentation, add a more 
sophisticated rendering loop, add lighting using the Phong reflection model, add a sky box, and add cube outlines to better distinguish
cubes of similiar color. Eventually, I would also like to implement a state machine to better handle state.
