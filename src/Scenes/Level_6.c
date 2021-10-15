#include "Level_6.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

void Init_Level_6_Spec(int index) {
  g_level_specs[index] =   (Level_Spec){
    .menu_camera_x_length = L6_TOTAL + 50,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L6_BUFFER*2 + L6_TOTAL
  };
}

Level_6_Builder Level_6_Builder_init(Level_6_Builder* self) {

  Level_6_Builder l6_builder = {
    ._super = Level_Builder_init()
  };

  l6_builder._super.build_level_entities = Build_Level_6_Entities;
  l6_builder._super._sub = self;

  return l6_builder;

}

void Build_Level_6_Entities(Level_Builder* builder) {

  Level_6_Builder* l6_builder = builder->_sub;

  builder->player = Create_Player();

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1);

  for (int i = 0; i < L6_HS2_COUNT; i++) {

    l6_builder->hs2_arr[i] = Create_Hook_Surface2(
      L6_HS2_POSITION_ARR[i],
      L6_HS2_SCALE_ARR[i]
    );

  }

  for (int i = 0; i < L6_GEM_COUNT; i++) {

    l6_builder->gem_arr[i] = Create_Gem(L6_GEM_POSITION_ARR[i]);

  }
  builder->hs2_arr = l6_builder->hs2_arr;
  builder->gem_arr = l6_builder->gem_arr;
  builder->hs2_count = L6_HS2_COUNT;
  builder->gem_count = L6_GEM_COUNT;

  // builder->bg = Create_Background(L6_WIDTH,L6_HEIGHT);

}

void Load_Level_6(geScene* scene) {

  Level_6_Builder l6_builder = Level_6_Builder_init(&l6_builder);

  Build_Level(0, &l6_builder._super, scene);

}
