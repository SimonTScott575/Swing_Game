#ifndef LEVEL_2_H
#define LEVEL_2_H

#include <Game_Engine/Game_Engine.h>

#include "../Scenes.h"

#include "Level_Builder.h"

#include "../Entities/Player.h"
#include "../Entities/Rope.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Gem.h"
#include "../Entities/Portal.h"
#include "../Entities/Background.h"

#define L2_A 10.0f
#define L2_B 10.0f
#define L2_C 5.0f
#define L2_BUFFER 1000.0f
#define L2_HW (L2_A+L2_B+L2_C)
#define L2_TOTAL (2*L2_HW)

// <A><B><C>
//  _______________
// |   _       _   |
// |  |_|  *  |_|  |
// |               |
// |   *   BE  *   |
// |   _       _   |
// |  |_|  *  |_|  |
// |_______________|
// Resulting shape is square

typedef
struct Level_2_Builder {

  Level_Builder _super;

  // Hook_Surface* hs_arr[1];
  Hook_Surface* hs_arr[8];
  Gem* gem_arr[4];

} Level_2_Builder;

Level_2_Builder Level_2_Builder_init(Level_2_Builder* self);
void Build_Level_2_Entities(Level_Builder* builder);
void Load_Level_2(geScene* scene);

void Init_Level_2_Spec(int index);
void Load_Level_2(geScene* scene);

#endif
