#ifndef LEVEL_4_H
#define LEVEL_4_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Hook_Surface2.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L4_HS2_COUNT 6
#define L4_GEM_COUNT L4_HS2_COUNT

#define L4_MAX_R 30.0f
#define L4_MIN_R 5.0f
#define L4_MAX_SCALE 10.0f
#define L4_MIN_SCALE 1.0f
#define L4_TOTAL ( 2*( L4_MAX_SCALE/2 + L4_MAX_R ) )
#define L4_BUFFER 1000.0f

#define L4_HEIGHT (2*L4_BUFFER + L4_TOTAL)
#define L4_WIDTH L4_HEIGHT

void Load_Level_4(geScene* scene);

typedef
struct Level_4_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface2* hs2_arr[L4_HS2_COUNT];
  Gem* gem_arr[L4_GEM_COUNT];

} Level_4_Builder;

Level_4_Builder Level_4_Builder_init(Level_4_Builder* self);
void Build_Level_4_Entities(Level_Builder* builder);

void Init_Level_4_Spec();
void Load_Level_4(geScene* scene);

#endif
