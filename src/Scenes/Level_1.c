#include "Level_1.h"

Level_1_Builder Level_1_Builder_init(Level_1_Builder* self) {

  Level_1_Builder l1_builder = {
    ._super = Level_Builder_init()
  };

  l1_builder._super.build_level_entities = Build_Level_1_Entities;
  l1_builder._super._sub = self;

  return l1_builder;

}

void Build_Level_1_Entities(Level_Builder* builder) {

  Level_1_Builder* l1_builder = builder->_sub;

  builder->player = Create_Player(builder->scene);
  builder->portal = Create_Portal((mVector2f){{L1_TOTAL-L1_A,0}}, 1, builder->scene);

  l1_builder->hs_arr[1-1] = Create_Hook_Surface(
    (mVector2f){{ 0, -L1_E/2-L1_D - L1_BUFFER/2 }},
    (mVector2f){{L1_TOTAL+L1_BUFFER*2, L1_BUFFER}},
    builder->scene
  );
  l1_builder->hs_arr[2-1] = Create_Hook_Surface(
    (mVector2f){{ 0, L1_E/2+L1_D + L1_BUFFER/2 }},
    (mVector2f){{L1_TOTAL+L1_BUFFER*2, L1_BUFFER}},
    builder->scene
  );
  l1_builder->hs_arr[3-1] = Create_Hook_Surface(
    (mVector2f){{ 0 - L1_A/2 - L1_BUFFER/2, 0 }},
    (mVector2f){{L1_BUFFER, L1_D+2*L1_E}},
    builder->scene
  );
  l1_builder->hs_arr[4-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L1_TOTAL-L1_A/2 + L1_BUFFER/2, 0 }},
    (mVector2f){{L1_BUFFER, L1_D+2*L1_E}},
    builder->scene
  );
  l1_builder->hs_arr[5-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L1_A/2 + L1_B/2, -L1_E/2 - L1_D/2 }},
    (mVector2f){{L1_B, L1_D}},
    builder->scene
  );
  l1_builder->hs_arr[6-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L1_A/2 + L1_B + L1_C + L1_B/2, L1_E/2 + L1_D/2 }},
    (mVector2f){{L1_B, L1_D}},
    builder->scene
   );

  mVector2f gem_positions[1] = {
    (mVector2f){{0 + L1_A/2 + L1_B + L1_C/2,0}}
  };
  l1_builder->gem_arr[0]  = Create_Gem(gem_positions[0], builder->scene);

  builder->hs_arr = l1_builder->hs_arr;
  builder->gem_arr = l1_builder->gem_arr;
  builder->hs_count = 6;
  builder->gem_count = 1;

  // builder->bg = Create_Background((L1_TOTAL-L1_A/2)*2,(L1_TOTAL-L1_A/2)*2);

  if (builder->as_scene) {
    builder->instruction_1 = Create_Menu_Text(
      "1) LEFT CLICK + W/S",
      "../Resources/Fonts/Fira/FiraSans-Heavy.ttf",
      0,0,
      0,-6,
      4,
      builder->scene
    );
    builder->instruction_2 = Create_Menu_Text(
      "2) PRESS A/D",
      "../Resources/Fonts/Fira/FiraSans-Heavy.ttf",
      0,0,
      5,6,
      4,
      builder->scene
    );
  }

}

void Init_Level_1_Spec(int index) {
  g_level_specs[index] = (Level_Spec){
    .menu_camera_x_length = ( L1_A*2 + 2*L1_B + L1_C ) + 10, // distance level select camera 0 to edge,,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L1_BUFFER*2 + L1_TOTAL
  };
}

void Load_Level_1(geScene* scene) {

  Level_1_Builder l1_builder = Level_1_Builder_init(&l1_builder);

  Build_Level(0, &l1_builder._super, scene);

}
