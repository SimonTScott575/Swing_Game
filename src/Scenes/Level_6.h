#ifndef LEVEL_6_H
#define LEVEL_6_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#define L6_HS2_COUNT 7
#define L6_GEM_COUNT 6

#define L6_HS2_POSITION_ARR (mVector2f[L6_HS2_COUNT]){ \
  {{-10, 10}}, \
  {{-8, -5}}, \
  {{ 2, -11}}, \
  {{ 10,  7}}, \
  {{ 8,  1}}, \
  {{-15, -12}}, \
  {{ 15, -7}} \
}
#define L6_HS2_SCALE_ARR (mVector2f[L6_HS2_COUNT]){ \
  {{10,10}}, \
  {{3,3}}, \
  {{6,6}}, \
  {{2,2}}, \
  {{1,1}}, \
  {{2,2}}, \
  {{5,5}} \
}
#define L6_GEM_POSITION_ARR (mVector2f[L6_GEM_COUNT]){ \
  {{-10 + 6*0.27,  10 + 6*0.96 }}, \
  {{-10 + 6*0.707, 10 + 6*0.707 }}, \
  {{-10 + 6*0.97,  10 + 6*0.24 }}, \
  {{ 2,           -11 + 3 + 1}}, \
  {{-15,          -12 + 1 + 1}}, \
  {{ 10 + 2*0.707,   7 - 2*0.707}} \
}

#define L6_TOTAL (15+5)
#define L6_BUFFER 1000

typedef
struct Level_6_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface2* hs2_arr[L6_HS2_COUNT];
  Gem* gem_arr[L6_GEM_COUNT];

} Level_6_Builder;

Level_6_Builder Level_6_Builder_init(Level_6_Builder* self);
void Build_Level_6_Entities(Level_Builder* builder);

void Init_Level_6_Spec();
void Load_Level_6(geScene* scene);

#endif
