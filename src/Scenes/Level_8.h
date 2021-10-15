#ifndef LEVEL_8_H
#define LEVEL_8_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#define L8_HS_COUNT 5
#define L8_HS2_COUNT 3
#define L8_GEM_COUNT 4

#define L8_HS_POSITIONS (mVector2f[L8_HS_COUNT]){ \
  {{-20,-5}}, \
  {{5, -15}}, \
  {{5+15,-10}}, \
  {{-8,7}}, \
  {{3,-8}} \
}
#define L8_HS_SCALES (mVector2f[L8_HS_COUNT]){ \
  {{15,15}}, \
  {{15,4}}, \
  {{7,7}}, \
  {{10,3}}, \
  {{1.5,1.5}} \
}
#define L8_HS2_POSITIONS (mVector2f[L8_HS2_COUNT]){ \
  {{10,5}}, \
  {{10,12}}, \
  {{10,17}}, \
}
#define L8_HS2_SCALES (mVector2f[L8_HS2_COUNT]){ \
  {{2,2}}, \
  {{2,2}}, \
  {{2,2}}, \
}
#define L8_GEM_POSITIONS (mVector2f[L8_GEM_COUNT]){ \
  {{3,-11}}, \
  {{10,5+(12-5)/2.0f}}, \
  {{10,12+(17-12)/2.0f}}, \
  {{-8-4,4}} \
}

#define L8_TOTAL ( 2 * (20.0f+7.5f) )
#define L8_BUFFER 1000

typedef
struct Level_8_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[L8_HS_COUNT];
  Hook_Surface2* hs2_arr[L8_HS2_COUNT];
  Gem* gem_arr[L8_GEM_COUNT];

} Level_8_Builder;

Level_8_Builder Level_8_Builder_init(Level_8_Builder* self);
void Build_Level_8_Entities(Level_Builder* builder);

void Init_Level_8_Spec(int index);
void Load_Level_8(geScene* scene);

#endif
