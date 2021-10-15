#ifndef LEVEL_3_H
#define LEVEL_3_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#define L3_PILLAR1_COLS 4 // MUST be even
#define L3_PILLAR_COUNT (L3_PILLAR1_COLS*3 - 2)
#define L3_HS_COUNT (L3_PILLAR_COUNT+4)
#define L3_GEM_COUNT (L3_PILLAR1_COLS*3 - 2)

#define L3_A 10.0f
// #define L3_B 10.0f
#define L3_C 2.0f
#define L3_D 10.0f
#define L3_E 10.0f
#define L3_F 10.0f
#define L3_BUFFER 1000.0f
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
struct Level_3_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[L3_HS_COUNT];
  Gem* gem_arr[L3_GEM_COUNT];

} Level_3_Builder;

Level_3_Builder Level_3_Builder_init(Level_3_Builder* self);
void Build_Level_3_Entities(Level_Builder* builder);
void Load_Level_3(geScene* scene);

void Init_Level_3_Spec(int index);
void Load_Level_3(geScene* scene);

#endif
