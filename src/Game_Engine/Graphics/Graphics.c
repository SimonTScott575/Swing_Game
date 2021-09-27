#include <Game_Engine/Graphics/Graphics.h>

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void grInit(int32_t X_pixels, int32_t Y_pixels) {

  // grInit_Types();
  //
  // grInit_Colours();

  grInit_Mesh();

  grInit_Screen();

  grInit_Text_Renderer();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

//TODO: grTerminate() //?
