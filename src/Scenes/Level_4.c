#include "Level_4.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"
// #include "../Scenes/Level_4_Basic_Build.h"

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

  builder->player = Create_Player();

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1);

  #if L4_HS2_COUNT != L4_GEM_COUNT
    #error L4 HS2 AND GEM COUNT DONT MATCH
  #endif

  for (int i = 0; i < L4_HS2_COUNT; i++) {

    float r = L4_MIN_R + (L4_MAX_R - L4_MIN_R)/(i+1);
    float x_pos = r*cos( M_PI*3/4.0f + M_PI/4 * i );
    float y_pos = r*sin( M_PI*3/4.0f + M_PI/4 * i );
    float s = L4_MIN_SCALE + (L4_MAX_SCALE - L4_MIN_SCALE)/(i+1);
    l4_builder->hs2_arr[i] = Create_Hook_Surface2(
      (mVector2f){{ x_pos, y_pos }},
      (mVector2f){{ s, s }}
    );

    l4_builder->gem_arr[i] = Create_Gem((mVector2f){{x_pos, y_pos + s/2 + 0.5}});

  }
  builder->hs2_arr = l4_builder->hs2_arr;
  builder->gem_arr = l4_builder->gem_arr;
  builder->hs2_count = L4_HS2_COUNT;
  builder->gem_count = L4_GEM_COUNT;

  builder->bg = Create_Background(L4_WIDTH,L4_HEIGHT);

}

void Load_Level_4(geScene* scene) {

  Level_4_Builder l4_builder = Level_4_Builder_init(&l4_builder);

  Build_Level(0, &l4_builder._super, scene);

}
