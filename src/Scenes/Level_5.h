#ifndef LEVEL_5_H
#define LEVEL_5_H

#include <Game_Engine/Game_Engine.h>

#include "Level_Builder.h"

#define L5_HS2_COUNT 1
#define L5_GEM_COUNT 1

#define L5_TOTAL 20
#define L5_BUFFER 20

#define L5_WIDTH 100
#define L5_HEIGHT 100

void Load_Level_5(geScene* scene);

typedef
struct Level_5_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface2* hs2_arr[L5_HS2_COUNT];
  Gem* gem_arr[L5_GEM_COUNT];

} Level_5_Builder;

Level_5_Builder Level_5_Builder_init(Level_5_Builder* self);
void Build_Level_5_Entities(Level_Builder* builder);
void Load_Level_5(geScene* scene);

#endif
