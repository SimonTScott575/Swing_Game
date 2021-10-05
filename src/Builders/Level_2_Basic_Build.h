#ifndef LEVEL_2_BASIC_BUILD_H
#define LEVEL_2_BASIC_BUILD_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L2_A 10.0f
#define L2_B 10.0f
#define L2_C 5.0f
#define L2_BUFFER 30.0f
#define L2_HW (L2_A+L2_B+L2_C)
#define L2_TOTAL (2*L2_HW)

// <A><B><C>
//  _______________
// |   _       _   |
// |  |_|  *  |_|  |
// |               |
// |   *   BE  *   |
// |   _       _   |
// |  |_|  *  |_|  |
// |_______________|
// Resulting shape is square

typedef
struct Level_2_Basic_Build {

  int build_with_physics;

  Player* player;

  Rope* rope;

  Gem* gem1;
  Gem* gem2;
  Gem* gem3;
  Gem* gem4;

  Portal* portal;

  Hook_Surface* hs1;
  Hook_Surface* hs2;
  Hook_Surface* hs3;
  Hook_Surface* hs4;
  Hook_Surface* hs5;
  Hook_Surface* hs6;
  Hook_Surface* hs7;
  Hook_Surface* hs8;

  Background* bg;

} Level_2_Basic_Build;

Level_2_Basic_Build Level_2_Basic_Build_init(int build_with_physics);
void Load_Entity_Player_Level_2_Basic_Build(Level_2_Basic_Build* build);
void Load_Entities_Level_2_Basic_Build(float x, mFrame2D* frame, Level_2_Basic_Build* build);
void Set_Level_2_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_2_Basic_Build* build);
void Add_Entities_Level_2_Basic_Build(geScene* scene, Level_2_Basic_Build* build);

#endif
