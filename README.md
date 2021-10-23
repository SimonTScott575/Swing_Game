# *Swing*

*Swing* is a small time trial based game.

*System requirements:*

 - *Operating system:* Windows 10 64-bit
 - *Processor:* x86-64
 - OpenGL 3.3 or later
 
## How To Play

Download the Swing_Game folder and unzip/extract.  Open the folder called "bin" and double click Swing.exe.

*Alternative CMake compilation instructions coming soon.*

Collect all the gems fast enough to progress on to the next level.  Hold left click to shoot a rope.  Use W/S to climb the rope and A/D to move left and right.

## Documentation

The game is written in C with OpenGL, the standard library and a small number of external libraries:

 - **glad/GLFW:** gives access to OpenGL and provides an easy to use interface for creating a window and taking user input.

 - **stbi:** converts images from a given file format, such as jpeg or png, to RGBA values.

 - **freetype:** produces images of text from a given file format such as ttf or otf.

A game engine library was written using the above including a basic rendering engine, physics engine, template based data structures and a vector and matrix maths library.