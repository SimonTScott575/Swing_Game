#include "Level_1.h"
#include "../Glow.h"

#include "../Builders/End_Level_Menu_Build.h"
#include "../Builders/Level_UI_Build.h"
#include "../Builders/Level_1_Surfaces_Build.h"

#include "../Entities/Camera.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"

#include "../Components/Gem_Controller.h"

void Load_Scene_1(geScene* scene) {

  Level_UI_Build level_ui_build;
  End_Level_Menu_Build end_level_menu_build;
  Level_1_Surfaces_Build level_1_surfaces_build = Level_1_Surfaces_Build_init(1);

  // ===
  // ECS
  // ===

  Load_Entity_Player_Level_1_Surfaces_Build(0, &level_1_surfaces_build);

  Camera* camera = Create_Camera(level_1_surfaces_build.player->frame, 20);

  Load_Entities_Level_1_Surfaces_Build(0, camera->frame, camera->cc, &level_1_surfaces_build);

  //
  Load_Entities_Level_UI_Build(&level_ui_build);

  //
  Load_Entities_End_Level_Menu_Build(level_1_surfaces_build.portal->pc,
                                     level_ui_build.timer->clock,
                                     level_1_surfaces_build.player->pc,
                                     &end_level_menu_build);

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

  Set_Level_1_Surfaces_Build(camera->camera2D, rs, rb_sys, &level_1_surfaces_build);

  rb_sys->gravity = (mVector2f){0,-5};

  camera->cc->rs = rs;

  //
  Set_Level_UI_Build(&level_ui_build);

  //
  Set_End_Level_Menu_Build(&end_level_menu_build);

  // ===
  // Add
  // ===

  geAdd_Entity(camera->_super, scene); //!!! should be add at start

  Add_Entities_Level_1_Surfaces_Build(scene, &level_1_surfaces_build);

  Add_Entities_Level_UI_Build(scene, &level_ui_build);

  Add_Entities_End_Level_Menu_Build(scene, &end_level_menu_build);

  // -------
  // Systems
  // -------

  geAdd_System(rs->_super, scene);
  geAdd_System(rb_sys->_super, scene);

  Add_Systems_Level_UI_Build(scene, &level_ui_build);

  Add_Systems_End_Level_Menu_Build(scene, &end_level_menu_build);

}
