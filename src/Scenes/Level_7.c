#include "Level_7.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

void Init_Level_7_Spec(int index) {
  g_level_specs[index] =   (Level_Spec){
    .menu_camera_x_length = L7_TOTAL + 50,
    .menu_camera_x_pos = -L7_B/2 + L7_TOTAL/2.0f,
    .menu_camera_y_pos = L7_B/2 - (L7_B/2 + L7_A)/2.0f,

    .max_x_length = L7_BUFFER*2 + L7_TOTAL
  };
}

Level_7_Builder Level_7_Builder_init(Level_7_Builder* self) {

  Level_7_Builder l7_builder = {
    ._super = Level_Builder_init()
  };

  l7_builder._super.build_level_entities = Build_Level_7_Entities;
  l7_builder._super._sub = self;

  return l7_builder;

}

void Build_Level_7_Entities(Level_Builder* builder) {

  Level_7_Builder* l7_builder = builder->_sub;

  builder->player = Create_Player();

  builder->portal = Create_Portal(
    (mVector2f){{L7_B/2 + L7_C/2 + L7_PILLAR_COUNT*L7_C, -L7_A}},
    1
  );

  l7_builder->hs_arr[0] = Create_Hook_Surface(
    (mVector2f){{-L7_B/2-L7_BUFFER/2,0}},
    (mVector2f){{L7_BUFFER,L7_B}}
  );
  l7_builder->hs_arr[1] = Create_Hook_Surface(
    (mVector2f){{L7_B/2 - (L7_B+L7_BUFFER)/2, -L7_B/2 - L7_A/2}},
    (mVector2f){{L7_B+L7_BUFFER,L7_A}}
  );
  l7_builder->hs_arr[2] = Create_Hook_Surface(
    (mVector2f){{-L7_B/2 + L7_TOTAL/2, L7_B/2 + L7_BUFFER/2}},
    (mVector2f){{L7_TOTAL + 2*L7_BUFFER, L7_BUFFER}}
  );
  l7_builder->hs_arr[3] = Create_Hook_Surface(
    (mVector2f){{-L7_B/2 + L7_TOTAL/2, -L7_B/2 - L7_A - L7_BUFFER/2}},
    (mVector2f){{L7_TOTAL + 2*L7_BUFFER,L7_BUFFER}}
  );
  l7_builder->hs_arr[4] = Create_Hook_Surface(
    (mVector2f){{-L7_B/2 + L7_TOTAL + L7_BUFFER/2, 0}},
    (mVector2f){{L7_BUFFER,L7_BUFFER}}
  );

  for (int i = 0; i < L7_PILLAR_COUNT; i++) {

    l7_builder->hs_arr[5+i] = Create_Hook_Surface(
      (mVector2f){{L7_B/2 + L7_C*(i+1), L7_B/2 - L7_A/2 - (i%2)*L7_B}},
      (mVector2f){{L7_D,L7_A}}
    );

  }

  for (int i = 0; i < L7_GEM_COUNT; i++) {

    l7_builder->gem_arr[i] = Create_Gem(
      (mVector2f){{ L7_B/2 + L7_C*(i+1), -L7_A*(1 - i%2) }}
    );

  }
  builder->hs_arr = l7_builder->hs_arr;
  builder->gem_arr = l7_builder->gem_arr;
  builder->hs_count = L7_HS_COUNT;
  builder->gem_count = L7_GEM_COUNT;

  // builder->bg = Create_Background(L7_WIDTH,L7_HEIGHT);

}

void Load_Level_7(geScene* scene) {

  Level_7_Builder l7_builder = Level_7_Builder_init(&l7_builder);

  Build_Level(0, &l7_builder._super, scene);

}
