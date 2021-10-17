#include "Level_2.h"

Level_2_Builder Level_2_Builder_init(Level_2_Builder* self) {

  Level_2_Builder l2_builder = {
    ._super = Level_Builder_init()
  };

  l2_builder._super.build_level_entities = Build_Level_2_Entities;
  l2_builder._super._sub = self;

  return l2_builder;

}

void Build_Level_2_Entities(Level_Builder* builder) {

  Level_2_Builder* l2_builder = builder->_sub;

  builder->player = Create_Player(builder->scene);

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1, builder->scene);

  mVector2f gem_positions[4] = {
    {{0 + L2_A, 0   }},
    {{0 - L2_A, 0   }},
    {{0 + 0,    L2_A}},
    {{0 + 0,   -L2_A}}
  };

  l2_builder->gem_arr[1-1] = Create_Gem(gem_positions[0], builder->scene);
  l2_builder->gem_arr[2-1] = Create_Gem(gem_positions[1], builder->scene);
  l2_builder->gem_arr[3-1] = Create_Gem(gem_positions[2], builder->scene);
  l2_builder->gem_arr[4-1] = Create_Gem(gem_positions[3], builder->scene);

  l2_builder->hs_arr[1-1] = Create_Hook_Surface(
    (mVector2f){{ 0, -L2_HW-L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }},
    builder->scene
  );
  l2_builder->hs_arr[2-1] = Create_Hook_Surface(
    (mVector2f){{ 0, L2_HW+L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }},
    builder->scene
  );
  l2_builder->hs_arr[3-1] = Create_Hook_Surface(
    (mVector2f){{ 0 -L2_HW-L2_BUFFER/2,  0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }},
    builder->scene
  );
  l2_builder->hs_arr[4-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_HW+L2_BUFFER/2, 0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }},
    builder->scene
  );
  l2_builder->hs_arr[5-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_C+L2_B/2, L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }},
    builder->scene
  );
  l2_builder->hs_arr[6-1] = Create_Hook_Surface(
    (mVector2f){{ 0 - (L2_C+L2_B/2), L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }},
    builder->scene
  );
  l2_builder->hs_arr[7-1] = Create_Hook_Surface(
    (mVector2f){{ 0 - (L2_C+L2_B/2), -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }},
    builder->scene
  );
  l2_builder->hs_arr[8-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_C+L2_B/2, -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }},
    builder->scene
  );

  builder->hs_arr = l2_builder->hs_arr;
  builder->gem_arr = l2_builder->gem_arr;
  builder->gem_count = 4;
  builder->hs_count = 8;

  // builder->bg = Create_Background(L2_TOTAL,L2_TOTAL);

}

void Init_Level_2_Spec(int index) {
  g_level_specs[index] = (Level_Spec){
    .menu_camera_x_length = L2_TOTAL + 15,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L2_BUFFER*2 + L2_TOTAL
  };
}

void Load_Level_2(geScene* scene) {

  Level_2_Builder l2_builder = Level_2_Builder_init(&l2_builder);

  Build_Level(0, &l2_builder._super, scene);

}
