#include <Game_Engine/Game_Engine.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int geInit() {

  int check = glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  return check;

}

void geTerminate() {

  glfwTerminate();

}

void geProcess_Events() {

  geSet_Input_States_ZERO( &geGet_Active_Game()->input_states );

  glfwPollEvents();

}
