#include <Game_Engine/Graphics/Graphics.h>

#include <stdio.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static bool is_init = false;

void grInit() {

  if (is_init) { return; }

  grInit_Types();
  grInit_Colours();
  grInit_Mesh();
  grInit_Screen();
  grInit_Text_Renderer();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  is_init = true;

}

//TODO: grTerminate() //?
