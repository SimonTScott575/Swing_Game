#ifndef LEVEL_1_H
#define LEVEL_1_H

//TEMP
#include "../Scenes/Level_1_Surfaces_Build.h"

#include <Game_Engine/Game_Engine.h>

#include "Level_Builder.h"

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

typedef
struct Level_1_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[8];
  Gem* gem_arr[4];

} Level_1_Builder;

Level_1_Builder Level_1_Builder_init(Level_1_Builder* self);
void Build_Level_1_Entities(Level_Builder* builder);
void Load_Level_1(geScene* scene);

#endif
