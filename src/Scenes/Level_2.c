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

  builder->player = Create_Player();

  builder->portal = Create_Portal((mVector2f){{0,0}}, 1);

  mVector2f gem_positions[4] = {
    {{0 + L2_A, 0   }},
    {{0 - L2_A, 0   }},
    {{0 + 0,    L2_A}},
    {{0 + 0,   -L2_A}}
  };

  l2_builder->gem_arr[1-1] = Create_Gem(gem_positions[0]);
  l2_builder->gem_arr[2-1] = Create_Gem(gem_positions[1]);
  l2_builder->gem_arr[3-1] = Create_Gem(gem_positions[2]);
  l2_builder->gem_arr[4-1] = Create_Gem(gem_positions[3]);

  l2_builder->hs_arr[1-1] = Create_Hook_Surface(
    (mVector2f){{ 0, -L2_HW-L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }}
  );
  l2_builder->hs_arr[2-1] = Create_Hook_Surface(
    (mVector2f){{ 0, L2_HW+L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }}
  );
  l2_builder->hs_arr[3-1] = Create_Hook_Surface(
    (mVector2f){{ 0 -L2_HW-L2_BUFFER/2,  0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }}
  );
  l2_builder->hs_arr[4-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_HW+L2_BUFFER/2, 0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }}
  );
  l2_builder->hs_arr[5-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_C+L2_B/2, L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }}
  );
  l2_builder->hs_arr[6-1] = Create_Hook_Surface(
    (mVector2f){{ 0 - (L2_C+L2_B/2), L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }}
  );
  l2_builder->hs_arr[7-1] = Create_Hook_Surface(
    (mVector2f){{ 0 - (L2_C+L2_B/2), -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }}
  );
  l2_builder->hs_arr[8-1] = Create_Hook_Surface(
    (mVector2f){{ 0 + L2_C+L2_B/2, -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }}
  );

  builder->hs_arr = l2_builder->hs_arr;
  builder->gem_arr = l2_builder->gem_arr;
  builder->gem_count = 4;
  builder->hs_count = 8;

  builder->bg = Create_Background(L2_TOTAL,L2_TOTAL);

}

void Load_Level_2(geScene* scene) {

  Level_2_Builder l2_builder = Level_2_Builder_init(&l2_builder);

  Build_Level(0, &l2_builder._super, scene);

}

// #include "../Glow.h"
//
// #include "../Scenes/End_Level_Menu_Build.h"
// #include "../Scenes/Level_UI_Build.h"
// #include "../Scenes/Level_2_Basic_Build.h"
//
// #include "../Entities/Camera.h"
// #include "../Entities/UI_Camera.h"
// #include "../Entities/UI_Manager.h"
// #include "../Entities/Menu_Button.h"
// #include "../Entities/Timer.h"
//
// #include "../Components/Gem_Controller.h"
//
// void Load_Level_2(geScene* scene) {
//
//   Level_2_Basic_Build level_2_basic_build = Level_2_Basic_Build_init(1);
//
//   // ========
//   // Load ECS
//   // ========
//
//   // --------
//   // Entities
//   // --------
//
//   Load_Entity_Player_Level_2_Basic_Build(&level_2_basic_build);
//
//   Camera* camera = Create_Camera(level_2_basic_build.player->frame, 20);
//
//   Load_Entities_Level_2_Basic_Build(0, camera->frame, &level_2_basic_build);
//
//   //
//   Level_UI_Build level_ui_build;
//   Load_Entities_Level_UI_Build(&level_ui_build);
//
//   //
//   End_Level_Menu_Build end_level_menu_build;
//
//   Load_Entities_End_Level_Menu_Build(level_2_basic_build.portal->pc, level_ui_build.timer->clock, level_2_basic_build.player->pc, &end_level_menu_build);
//
//   // -------
//   // Systems
//   // -------
//
//   grRendering_System2D* rs = grCreate_Rendering_System2D(camera->camera2D);
//
//   phRB_System2D* rb_sys = new_phRB_System2D();
//
//   Load_Systems_Level_UI_Build(&level_ui_build);
//
//   Load_Systems_End_Level_Menu_Build(&end_level_menu_build);
//
//   // ===
//   // Set
//   // ===
//
//   rs->post_process = Glow_PP;
//
//   Set_Level_2_Basic_Build(camera->camera2D, rs, rb_sys, &level_2_basic_build);
//
//   //
//   camera->cc->rs = rs;
//
//   rb_sys->gravity = (mVector2f){{0,-5}};
//
//   //
//   Set_Level_UI_Build(&level_ui_build);
//
//   //
//   Set_End_Level_Menu_Build(&end_level_menu_build);
//
//   // ===
//   // Add
//   // ===
//
//   // -------
//   // Entites
//   // -------
//
//   geAdd_Entity(camera->_super, scene);
//
//   Add_Entities_Level_2_Basic_Build(scene, &level_2_basic_build);
//
//   Add_Entities_Level_UI_Build(scene, &level_ui_build);
//
//   Add_Entities_End_Level_Menu_Build(scene, &end_level_menu_build);
//
//   // -----
//   // Scene
//   // -----
//
//   geAdd_System(rs->_super, scene);
//   geAdd_System(rb_sys->_super, scene);
//
//   Add_Systems_Level_UI_Build(scene, &level_ui_build);
//
//   Add_Systems_End_Level_Menu_Build(scene, &end_level_menu_build);
//
// }
