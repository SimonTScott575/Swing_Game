#ifndef GR_GRAPHICS_H
#define GR_GRAPHICS_H

#ifdef GR_INCLUDE_OpenGL
  #include "../../../extern/glad/glad.h"
  #include "../../../extern/GLFW/glfw3.h"
#endif

#include <Game_Engine/Graphics/Formats/grColours.h>
#include <Game_Engine/Graphics/Formats/grTypes.h>

#include <Game_Engine/Graphics/grTexture.h>
#include <Game_Engine/Graphics/grMesh.h>
#include <Game_Engine/Graphics/grModel.h>
#include <Game_Engine/Graphics/grShader.h>
#include <Game_Engine/Graphics/grRenderer.h>
#include <Game_Engine/Graphics/grScreen.h>
#include <Game_Engine/Graphics/grText_Renderer.h>

#include <Game_Engine/Graphics/Defaults/grCamera.h>
#include <Game_Engine/Graphics/Defaults/grRendering_System.h>
#include <Game_Engine/Graphics/Defaults/grColour_Render.h>
#include <Game_Engine/Graphics/Defaults/grSprite.h>

void grInit();

//... grTerminate

#endif
