#include "Level_8.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

void Init_Level_8_Spec(int index) {
  g_level_specs[index] =   (Level_Spec){
    .menu_camera_x_length = L8_TOTAL + 25,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L8_BUFFER*2 + L8_TOTAL
  };
}

Level_8_Builder Level_8_Builder_init(Level_8_Builder* self) {

  Level_8_Builder l8_builder = {
    ._super = Level_Builder_init()
  };

  l8_builder._super.build_level_entities = Build_Level_8_Entities;
  l8_builder._super._sub = self;

  return l8_builder;

}

void Build_Level_8_Entities(Level_Builder* builder) {

  Level_8_Builder* l8_builder = builder->_sub;

  builder->player = Create_Player();

  builder->portal = Create_Portal(
    (mVector2f){{0,0}},
    1
  );

  for (int i = 0; i < L8_HS_COUNT; i++) {

    l8_builder->hs_arr[i] = Create_Hook_Surface(
      L8_HS_POSITIONS[i],
      L8_HS_SCALES[i]
    );

  }
  for (int i = 0; i < L8_HS2_COUNT; i++) {

    l8_builder->hs2_arr[i] = Create_Hook_Surface2(
      L8_HS2_POSITIONS[i],
      L8_HS2_SCALES[i]
    );

  }

  for (int i = 0; i < L8_GEM_COUNT; i++) {

    l8_builder->gem_arr[i] = Create_Gem(
      L8_GEM_POSITIONS[i]
    );

  }
  builder->hs_arr = l8_builder->hs_arr;
  builder->hs2_arr = l8_builder->hs2_arr;
  builder->gem_arr = l8_builder->gem_arr;
  builder->hs_count = L8_HS_COUNT;
  builder->hs2_count = L8_HS2_COUNT;
  builder->gem_count = L8_GEM_COUNT;

  // builder->bg = Create_Background(L8_WIDTH,L8_HEIGHT);

}

void Load_Level_8(geScene* scene) {

  Level_8_Builder l8_builder = Level_8_Builder_init(&l8_builder);

  Build_Level(0, &l8_builder._super, scene);

}
