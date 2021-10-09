#ifndef LEVEL_4_BASIC_BUILD_H
#define LEVEL_4_BASIC_BUILD_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Hook_Surface2.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L4_HS_COUNT 6
#define L4_GEM_COUNT L4_HS_COUNT

#define L4_MAX_R 20.0f
#define L4_MIN_R 3.0f
#define L4_MAX_SCALE 10.0f
#define L4_MIN_SCALE 1.0f
#define L4_TOTAL ( 2*( L4_MAX_SCALE/2 + L4_MAX_R ) )
#define L4_BUFFER 100

#define L4_HEIGHT (2*L4_BUFFER + L4_TOTAL)
#define L4_WIDTH L4_HEIGHT

typedef
struct Level_4_Basic_Build {

  int build_with_physics;

  Player* player;
  Rope* rope;

  Portal* portal;

  Gem* gems[L4_GEM_COUNT];
  Gem_Controller* gem_controllers[L4_GEM_COUNT];

  Hook_Surface2* hs_arr[L4_HS_COUNT];

  Background* bg;

} Level_4_Basic_Build;

Level_4_Basic_Build Level_4_Basic_Build_init(int build_with_physics);
void Load_Entity_Player_Level_4_Basic_Build(Level_4_Basic_Build* build);
void Load_Entities_Level_4_Basic_Build(float x, mFrame2D* frame, Level_4_Basic_Build* build);
void Set_Level_4_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_4_Basic_Build* build);
void Add_Entities_Level_4_Basic_Build(geScene* scene, Level_4_Basic_Build* build);

#endif
