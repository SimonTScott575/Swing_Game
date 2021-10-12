#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L1_A 8.0f
#define L1_B 4.0f
#define L1_C 2.0f
#define L1_D 1.5f
#define L1_E 2.0f
#define L1_BUFFER 1000.0f
#define L1_TOTAL (2*L1_A + 2*L1_B + L1_C)

// <---A---><--B--><C><--B--><---A--->
//  __________________       ________
// |                  |_____|        | D
// |   B     _____  *           E    | E
// |________|     |__________________| D
//

typedef
struct Level_1_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[6];
  Gem* gem_arr[1];

} Level_1_Builder;

Level_1_Builder Level_1_Builder_init(Level_1_Builder* self);
void Build_Level_1_Entities(Level_Builder* builder);

void Init_Level_1_Spec();
void Load_Level_1(geScene* scene);

#endif
