#ifndef LEVEL_7_H
#define LEVEL_7_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#define L7_PILLAR_COUNT 6 // MUST be even
#define L7_HS_COUNT (L7_PILLAR_COUNT+5)
#define L7_GEM_COUNT L7_PILLAR_COUNT

#define L7_A 20.0f
#define L7_B 10.0f
#define L7_C 15.0f
#define L7_D 2.0f

#define L7_TOTAL (L7_B + L7_C*(L7_PILLAR_COUNT+1))
#define L7_BUFFER 1000

//           D
//      <B><C>    D    D   D
//      ______________________
//  B  |o_    |   *   |   *   | B
//  ^     |   |   |   |   |   |
//  A     |   |   |   |   |   |
//  |     |   |   |   |   |   |
// \ /    |___*___|___*___|_O_| B

typedef
struct Level_7_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[L7_HS_COUNT];
  Gem* gem_arr[L7_GEM_COUNT];

} Level_7_Builder;

Level_7_Builder Level_7_Builder_init(Level_7_Builder* self);
void Build_Level_7_Entities(Level_Builder* builder);

void Init_Level_7_Spec();
void Load_Level_7(geScene* scene);

#endif
