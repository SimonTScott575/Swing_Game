#include <Game_Engine/Graphics/Formats/grColours.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct grColours grColours;

void grInit_Colours() {

  grColours.RGB = GL_RGB;
  grColours.RGBA = GL_RGBA;
  grColours.R = GL_RED;

}
