#include "Level_5.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

Level_5_Builder Level_5_Builder_init(Level_5_Builder* self) {

  Level_5_Builder l5_builder = {
    ._super = Level_Builder_init()
  };

  l5_builder._super.build_level_entities = Build_Level_5_Entities;
  l5_builder._super._sub = self;

  return l5_builder;

}

void Build_Level_5_Entities(Level_Builder* builder) {

  Level_5_Builder* l5_builder = builder->_sub;

  builder->player = Create_Player();

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1);

  #if L5_HS2_COUNT != L5_GEM_COUNT
   #error LEVEL 5 GEM AND HS COUNT NOT EQUAL
  #endif

  for (int i = 0; i < L5_HS2_COUNT; i++) {

    l5_builder->hs2_arr[i] = Create_Hook_Surface2(
      (mVector2f){{ 0, 3 }},
      (mVector2f){{ 1, 1 }}
    );

    l5_builder->gem_arr[i] = Create_Gem((mVector2f){{3, 3}});
    // l5_builder->gem_controllers[i] = l5_builder->gem_arr[i]->gc;

  }
  builder->hs2_arr = l5_builder->hs2_arr;
  builder->gem_arr = l5_builder->gem_arr;
  builder->hs2_count = L5_HS2_COUNT;
  builder->gem_count = L5_GEM_COUNT;

  builder->bg = Create_Background(L5_WIDTH,L5_HEIGHT);

}

void Load_Level_5(geScene* scene) {

  Level_5_Builder l5_builder = Level_5_Builder_init(&l5_builder);

  Build_Level(0, &l5_builder._super, scene);

}
