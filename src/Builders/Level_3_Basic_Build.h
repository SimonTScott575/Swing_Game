#ifndef LEVEL_3_BASIC_BUILD_H
#define LEVEL_3_BASIC_BUILD_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L3_PILLAR1_COLS 4 // MUST be even
#define L3_PILLAR_COUNT (L3_PILLAR1_COLS*3 - 2)
#define L3_GEM_COUNT (L3_PILLAR1_COLS*3 - 2)

#define L3_A 10.0f
// #define L3_B 10.0f
#define L3_C 2.0f
#define L3_D 10.0f
#define L3_E 10.0f
#define L3_F 10.0f
#define L3_BUFFER 10.0f
#define L3_HEIGHT (2*L3_D + 2*L3_E + L3_F)
#define L3_WIDTH ( 2 * L3_A * L3_PILLAR1_COLS )
#define L3_TOTAL L3_WIDTH


// <-A-><-A->
//  ___________ ... _
// |                 | D
// |    *   |        | E
// |    |   *        | F
// |    *   |        | E
// |___________ ... _| D
// C is column thickness
// width should be greater than height

typedef
struct Level_3_Basic_Build {

  int build_with_physics;

  Player* player;

  Rope* rope;

  Gem* gems[L3_GEM_COUNT];

  Portal* portal;

  Hook_Surface* hs1;
  Hook_Surface* hs2;
  Hook_Surface* hs3;
  Hook_Surface* hs4;
  Hook_Surface* hs_pillars[L3_PILLAR_COUNT];

  Background* bg;

} Level_3_Basic_Build;

Level_3_Basic_Build Level_3_Basic_Build_init(int build_with_physics);
void Load_Entity_Player_Level_3_Basic_Build(Level_3_Basic_Build* build);
void Load_Entities_Level_3_Basic_Build(float x, mFrame2D* frame, Level_3_Basic_Build* build);
void Set_Level_3_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_3_Basic_Build* build);
void Add_Entities_Level_3_Basic_Build(geScene* scene, Level_3_Basic_Build* build);

#endif
