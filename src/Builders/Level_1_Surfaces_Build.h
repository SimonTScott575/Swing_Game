#ifndef LEVEL_1_SURFACES_BUILD_H
#define LEVEL_1_SURFACES_BUILD_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Player.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Rope.h"
#include "../Entities/Gem.h"
#include "../Entities/Background.h"
#include "../Entities/Portal.h"

typedef
struct Level_1_Surfaces_Build {

  int build_with_physics;

  Player* player;
  Rope* rope;

  Gem* gem;
  Portal* portal;

  Hook_Surface* hs1;
  Hook_Surface* hs2;
  Hook_Surface* hs3;
  Hook_Surface* hs4;
  Hook_Surface* hs5;
  Hook_Surface* hs6;

  Background* bg;

} Level_1_Surfaces_Build;

Level_1_Surfaces_Build Level_1_Surfaces_Build_init(int build_with_physics);

void Load_Entity_Player_Level_1_Surfaces_Build(float x, Level_1_Surfaces_Build* build);
void Load_Entities_Level_1_Surfaces_Build(float x, mFrame2D* frame, Level_1_Surfaces_Build* build);
void Set_Level_1_Surfaces_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rs_sys, Level_1_Surfaces_Build* build);
void Add_Entities_Level_1_Surfaces_Build(geScene* scene, Level_1_Surfaces_Build* build);

#endif
