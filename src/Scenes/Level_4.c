#include "Level_4.h"

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"
#include "../Scenes/Level_4_Basic_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

void Load_Level_4(geScene* scene) {

  Level_4_Basic_Build level_4_basic_build = Level_4_Basic_Build_init(1);

  // ========
  // Load ECS
  // ========

  // --------
  // Entities
  // --------

  Load_Entity_Player_Level_4_Basic_Build(&level_4_basic_build);

  Camera* camera = Create_Camera(level_4_basic_build.player->frame, 20);

  Load_Entities_Level_4_Basic_Build(0, camera->frame, &level_4_basic_build);

  //
  Level_UI_Build level_ui_build;
  Load_Entities_Level_UI_Build(&level_ui_build);

  //
  End_Level_Menu_Build end_level_menu_build;

  Load_Entities_End_Level_Menu_Build(level_4_basic_build.portal->pc, level_ui_build.timer->clock, level_4_basic_build.player->pc, &end_level_menu_build);

  // -------
  // Systems
  // -------

  grRendering_System2D* rs = grCreate_Rendering_System2D(camera->camera2D);

  phRB_System2D* rb_sys = new_phRB_System2D();

  Load_Systems_Level_UI_Build(&level_ui_build);

  Load_Systems_End_Level_Menu_Build(&end_level_menu_build);

  // ===
  // Set
  // ===

  rs->post_process = Glow_PP;

  Set_Level_4_Basic_Build(camera->camera2D, rs, rb_sys, &level_4_basic_build);

  //
  camera->cc->rs = rs;
  camera->camera2D->background_colour[0]
    = camera->camera2D->background_colour[2]
    = camera->camera2D->background_colour[3]
    = 1;
  camera->camera2D->background_colour[1] = 0;

  rb_sys->gravity = (mVector2f){{0,-5}};

  //
  Set_Level_UI_Build(&level_ui_build);

  //
  Set_End_Level_Menu_Build(&end_level_menu_build);

  // ===
  // Add
  // ===

  // -------
  // Entites
  // -------

  geAdd_Entity(camera->_super, scene);

  Add_Entities_Level_4_Basic_Build(scene, &level_4_basic_build);

  Add_Entities_Level_UI_Build(scene, &level_ui_build);

  Add_Entities_End_Level_Menu_Build(scene, &end_level_menu_build);

  // -----
  // Scene
  // -----

  geAdd_System(rs->_super, scene);
  geAdd_System(rb_sys->_super, scene);

  Add_Systems_Level_UI_Build(scene, &level_ui_build);

  Add_Systems_End_Level_Menu_Build(scene, &end_level_menu_build);

}
