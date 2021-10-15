#include "Level_3.h"

Level_3_Builder Level_3_Builder_init(Level_3_Builder* self) {

  Level_3_Builder l3_builder = {
    ._super = Level_Builder_init()
  };

  l3_builder._super.build_level_entities = Build_Level_3_Entities;
  l3_builder._super._sub = self;

  return l3_builder;

}

void Build_Level_3_Entities(Level_Builder* builder) {

  Level_3_Builder* l3_builder = builder->_sub;

  builder->player = Create_Player();

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1);

  l3_builder->hs_arr[0] = Create_Hook_Surface(
    (mVector2f){{ 0, L3_HEIGHT/2 + L3_BUFFER/2 }},
    (mVector2f){{ L3_TOTAL + L3_BUFFER*2, L3_BUFFER }}
  );
  l3_builder->hs_arr[1] = Create_Hook_Surface(
    (mVector2f){{ 0, -L3_HEIGHT/2  - L3_BUFFER/2 }},
    (mVector2f){{ L3_TOTAL + L3_BUFFER*2, L3_BUFFER }}
  );
  l3_builder->hs_arr[2] = Create_Hook_Surface(
    (mVector2f){{ 0 - L3_WIDTH/2 - L3_BUFFER/2, 0 }},
    (mVector2f){{ L3_BUFFER, L3_HEIGHT }}
  );
  l3_builder->hs_arr[3] = Create_Hook_Surface(
    (mVector2f){{ 0 + L3_WIDTH/2 + L3_BUFFER/2, 0 }},
    (mVector2f){{ L3_BUFFER, L3_HEIGHT }}
  );

  for (int i = 0; i < L3_PILLAR1_COLS; i++) {

    l3_builder->hs_arr[4 + i] = Create_Hook_Surface(
      (mVector2f){{ - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A, 0 }},
      (mVector2f){{ L3_C, L3_F }}
    );

    mVector2f pos1 = (mVector2f){{
      0 - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A,
      L3_F/2 + L3_E/2
    }};
    mVector2f pos2 = (mVector2f){{
      0 - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A,
      - L3_F/2 - L3_E/2
    }};

    l3_builder->gem_arr[2*i] = Create_Gem(pos1);
    l3_builder->gem_arr[2*i+1] = Create_Gem(pos2);

  }
  int j = 0;
  for (int i = 0; i < L3_PILLAR1_COLS-1; i++) {

    l3_builder->hs_arr[4+L3_PILLAR1_COLS + 2*i] = Create_Hook_Surface(
      (mVector2f){{ 0 - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A, L3_F/2+L3_E/2 }},
      (mVector2f){{ L3_C, L3_E }}
    );
    l3_builder->hs_arr[4+L3_PILLAR1_COLS + 2*i+1] = Create_Hook_Surface(
      (mVector2f){{ 0 - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A, -L3_F/2-L3_E/2 }},
      (mVector2f){{ L3_C, L3_E }}
    );

    if (i != L3_PILLAR1_COLS/2 - 1) {

      mVector2f pos = (mVector2f){{
        0 - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A,
        0
      }};

      l3_builder->gem_arr[2*L3_PILLAR1_COLS + j] = Create_Gem(pos);

      // printf("%d %d\n", 2*L3_PILLAR1_COLS + j, L3_GEM_COUNT);

      j += 1;

    }

  }
  builder->hs_arr = l3_builder->hs_arr;
  builder->gem_arr = l3_builder->gem_arr;
  builder->hs_count = L3_HS_COUNT;
  builder->gem_count = L3_GEM_COUNT;

  // builder->bg = Create_Background(L3_WIDTH,L3_HEIGHT);

}

void Init_Level_3_Spec(int index) {
  g_level_specs[index] = (Level_Spec){
    .menu_camera_x_length = L3_WIDTH + 15,
    .menu_camera_x_pos = 0,
    .menu_camera_y_pos = 0,

    .max_x_length = L3_BUFFER*2 + L3_TOTAL
  };
}

void Load_Level_3(geScene* scene) {

  Level_3_Builder l3_builder = Level_3_Builder_init(&l3_builder);

  Build_Level(0, &l3_builder._super, scene);

}
