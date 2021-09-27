#ifndef GE_GAME_ENGINE_H
#define GE_GAME_ENGINE_H

#ifdef GE_INCLUDE_GLFW
  #include "../../extern/glad/glad.h"
  #include "../../extern/GLFW/glfw3.h"
#endif //? extern location doesn't really work

#include <Game_Engine/geInput_States.h>
#include <Game_Engine/geWindow.h>
#include <Game_Engine/geScene.h>
#include <Game_Engine/geGame.h>
#include <Game_Engine/geInput.h>

#include <Game_Engine/ECS/ECS.h>
#include <Game_Engine/dATUM/dATUM.h>
#include <Game_Engine/Maths/Maths.h>
#include <Game_Engine/UI/UI.h>
#include <Game_Engine/Physics/Physics.h>
#include <Game_Engine/Graphics/Graphics.h>

int geInit();
void geTerminate();

void geProcess_Events();

#endif
