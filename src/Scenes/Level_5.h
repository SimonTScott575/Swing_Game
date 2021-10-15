#ifndef LEVEL_5_H
#define LEVEL_5_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#define L5_HS_COUNT 6
#define L5_GEM_COUNT 5

#define L5_GEM_SEP 5.0f
#define L5_TOTAL 5.0f
#define L5_BUFFER 1000

typedef
struct Level_5_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[L5_HS_COUNT];
  Gem* gem_arr[L5_GEM_COUNT];

} Level_5_Builder;

Level_5_Builder Level_5_Builder_init(Level_5_Builder* self);
void Build_Level_5_Entities(Level_Builder* builder);

void Init_Level_5_Spec(int index);
void Load_Level_5(geScene* scene);

#endif
