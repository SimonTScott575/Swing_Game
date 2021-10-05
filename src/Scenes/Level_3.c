#include "Level_3.h"

#include "../Builders/End_Level_Menu_Build.h"
#include "../Builders/Level_UI_Build.h"
#include "../Builders/Level_3_Basic_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

void Load_Level_3(geScene* scene) {

  Level_3_Basic_Build level_3_basic_build = Level_3_Basic_Build_init(1);

  // ========
  // Load ECS
  // ========

  // --------
  // Entities
  // --------

  Load_Entity_Player_Level_3_Basic_Build(&level_3_basic_build);

  Camera* camera = Create_Camera(level_3_basic_build.player->frame, 20);

  Load_Entities_Level_3_Basic_Build(0, camera->frame, &level_3_basic_build);

  //
  Level_UI_Build level_ui_build;
  Load_Entities_Level_UI_Build(&level_ui_build);

  //
  End_Level_Menu_Build end_level_menu_build;

  Load_Entities_End_Level_Menu_Build(level_3_basic_build.portal->pc, level_ui_build.timer->clock, level_3_basic_build.player->pc, &end_level_menu_build);

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

  Set_Level_3_Basic_Build(camera->camera2D, rs, rb_sys, &level_3_basic_build);

  //
  camera->cc->rs = rs;

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

  Add_Entities_Level_3_Basic_Build(scene, &level_3_basic_build);

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
