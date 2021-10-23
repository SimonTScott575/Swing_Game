# *Swing*

*Swing* is a small time trial based game.

![](https://github.com/SimonTScott575/Swing_Game/blob/master/Resources/Demo.gif)

**System requirements:**

 - *Operating system:* Windows 10 64-bit
 - *Processor:* x86-64
 - OpenGL 3.3 or later
 
## How To Play

Download the Swing_Game folder and unzip/extract.  Open the folder called "bin" and double click Swing.exe.

Collect all the gems and make it to the goal fast enough to progress on to the next level.

Controls:

 - Hold left click to shoot a rope

 - Press W/D to climb/descend the rope

 - Press A/D to move left/right

 - Press escape to quit the level

## Documentation

The game is written in C with OpenGL, the standard library and a small number of external libraries:

 - **glad/GLFW:** gives access to OpenGL and provides an easy to use interface for creating a window and taking user input.

 - **stbi:** converts images from a given file format, such as jpeg or png, to RGBA values.

 - **freetype:** produces images of text from a given file format such as ttf or otf.

A game engine library was written using the above.  Code was written for a basic rendering engine, physics engine, template based data structures and a vector and matrix maths library.