#include "Level_4.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

Level_4_Builder Level_4_Builder_init(Level_4_Builder* self) {

  Level_4_Builder l4_builder = {
    ._super = Level_Builder_init()
  };

  l4_builder._super.build_level_entities = Build_Level_4_Entities;
  l4_builder._super._sub = self;

  return l4_builder;

}

void Build_Level_4_Entities(Level_Builder* builder) {

  Level_4_Builder* l4_builder = builder->_sub;

  builder->player = Create_Player(builder->scene);

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1, builder->scene);

  float prev_x_pos;
  float prev_y_pos;
  for (int i = 0; i < L4_HS2_COUNT; i++) {

    float r = L4_MIN_R + (L4_MAX_R - L4_MIN_R)*i/(float)(L4_HS2_COUNT-1);
    float x_pos = r*cos( M_PI*3/2.0f + M_PI/4 * i );
    float y_pos = r*sin( M_PI*3/2.0f + M_PI/4 * i );
    float s = L4_MIN_SCALE + (L4_MAX_SCALE - L4_MIN_SCALE)*i/(float)(L4_HS2_COUNT-1);
    l4_builder->hs2_arr[i] = Create_Hook_Surface2(
      (mVector2f){{ x_pos, y_pos }},
      (mVector2f){{ s, s }},
      builder->scene
    );

    if (0 < i && i-1 < L4_GEM_COUNT) {
      l4_builder->gem_arr[i-1] = Create_Gem(
        (mVector2f){{
          prev_x_pos + (x_pos-prev_x_pos)/2,
          prev_y_pos + (y_pos-prev_y_pos)/2
        }},
        builder->scene
      );
    }

    prev_x_pos = x_pos;
    prev_y_pos = y_pos;

  }
  builder->hs2_arr = l4_builder->hs2_arr;
  builder->gem_arr = l4_builder->gem_arr;
  builder->hs2_count = L4_HS2_COUNT;
  builder->gem_count = L4_GEM_COUNT;

  // builder->bg = Create_Background(L4_WIDTH,L4_HEIGHT);

}

void Init_Level_4_Spec(int index) {
  g_level_specs[index] = (Level_Spec){
    .menu_camera_x_length = L4_TOTAL + 15,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L4_BUFFER*2 + L4_TOTAL
  };
}

void Load_Level_4(geScene* scene) {

  Level_4_Builder l4_builder = Level_4_Builder_init(&l4_builder);

  Build_Level(0, &l4_builder._super, scene);

}
