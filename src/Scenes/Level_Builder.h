#ifndef LEVEL_BUILDER_H
#define LEVEL_BUILDER_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Camera.h"
#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Hook_Surface2.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"
#include "../Entities/Menu_Text.h"

// //TEMP
// #include "Level_5_Basic_Build.h"

typedef struct Level_Builder Level_Builder;

typedef void (*Build_Level_fn)(Level_Builder* level_builder);

// typedef
// struct Level_Generator {
//
//   // Player* player;
//   // Rope* rope;
//   // Portal* portal;
//   // Gem** gem_arr; // default : NULL
//   // Hook_Surface** hs_arr; // default : NULL
//   // Hook_Surface2** hs2_arr; // default : NULL
//   // Background* bg;
//
// } Level_Generator;

typedef
struct Level_Builder {

  bool as_scene;

  geScene* scene; // MUST be set non-NULL if as_scene == true

  // MUST SET BY USER
  Player* player;
  Rope* rope;
  Portal* portal;
  Gem** gem_arr; // default : NULL
  int gem_count;
  Hook_Surface** hs_arr; // default : NULL
  int hs_count;
  Hook_Surface2** hs2_arr; // default : NULL
  int hs2_count;

  // USER OPTIONAL
  Background* bg;

  Menu_Text* instruction_1;
  Menu_Text* instruction_2;

  // SET BY SUB TYPE
  Build_Level_fn build_level_entities;

  void* _sub;

} Level_Builder;

void Build_Level(float x_offset, Level_Builder* builder, geScene* scene);
void Build_Level_Basics_Load(float x_offset, geScene* scene, Level_Builder* builder);
void Build_Level_Basics_Set(grRendering_System2D* rs, Level_Builder* builder);
void Build_Level_Basics_Add(geScene* scene, Level_Builder* builder);

Level_Builder Level_Builder_init();

#endif
