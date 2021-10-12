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

void Init_Level_5_Spec() {
  g_level_specs[4] =   (Level_Spec){
    .menu_camera_x_length = L5_TOTAL + 50,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 13,

    .max_x_length = L5_BUFFER*2 + L5_TOTAL
  };
}

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

  builder->portal = Create_Portal((mVector2f){{0,(L5_GEM_COUNT+1)*L5_GEM_SEP}}, 1);

  for (int i = 0; i < L5_HS_COUNT; i++) {

    l5_builder->hs_arr[i] = Create_Hook_Surface(
      (mVector2f){{ ( 1 - 2*(i%2) )*3, (i+0.5)*L5_GEM_SEP }},
      (mVector2f){{ 1, 1 }}
    );

  }

  for (int i = 0; i < L5_GEM_COUNT; i++) {

    l5_builder->gem_arr[i] = Create_Gem((mVector2f){{0, L5_GEM_SEP*(i+1)}});

  }
  builder->hs_arr = l5_builder->hs_arr;
  builder->gem_arr = l5_builder->gem_arr;
  builder->hs_count = L5_HS_COUNT;
  builder->gem_count = L5_GEM_COUNT;

  // builder->bg = Create_Background(L5_WIDTH,L5_HEIGHT);

}

void Load_Level_5(geScene* scene) {

  Level_5_Builder l5_builder = Level_5_Builder_init(&l5_builder);

  Build_Level(0, &l5_builder._super, scene);

}
