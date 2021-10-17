#include "Main_Menu.h"

#include <stdbool.h>

#include "../Entities/UI_Camera.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Menu_Camera.h"
#include "../Entities/Background.h"
#include "../Entities/Menu_Text.h"
//TODO: should have better place to store Play and End_Game on click callbacks
#include "../Components/Level_Select_Navigator.h"

void Load_Main_Menu(geScene* scene) {

  bool load_fail = false;

  // ========
  // Load ECS
  // ========

  // --------
  // Entities
  // --------

  Menu_Text* title = Create_Menu_Text("SWING", "../Resources/Fonts/Fira/FiraSans-HeavyItalic.ttf", 0,0, 0,0.4, 1.5, scene);
  Menu_Text* play_text = Create_Menu_Text("PLAY", NULL, 0,0, 0,0.04, 0.7, scene);
  Menu_Text* quit_text = Create_Menu_Text("QUIT", NULL, 0,0, 0,-0.21, 0.7, scene);

  Menu_Camera* menu_camera = Create_Menu_Camera(50, scene);

  Background* bg = Create_Background(50,50, scene);

  grRendering_System2D* rs = grCreate_Rendering_System2D(&menu_camera->camera2D);

  UI_Camera* ui_camera = Create_UI_Camera(scene);

  Menu_Button* play_button = Create_Menu_Button(0,0, 0,0.1, 1,0.2,
                                                "../Resources/Textures/square_orange_256.png",
                                                On_Click_Play_Button,
                                                scene);
  Menu_Button* end_game_button = Create_Menu_Button(0,0, 0,-0.15, 1,0.2,
                                                    "../Resources/Textures/square_orange_256.png",
                                                    On_Click_End_Game_Button,
                                                    scene);

  // -------
  // Systems
  // -------

  grRendering_System2D* ui_rs = grCreate_Rendering_System2D(&ui_camera->camera);

  geUI_Manager* ge_uim = geCreate_UI_Manager(&ui_camera->camera);

  if (ui_rs == NULL || ge_uim == NULL) {
    goto end_scene_exception;
  }

  // ===
  // Set
  // ===

  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&bg->renderer, rs->_renderers);

  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&play_button->ui_r->_super, ui_rs->_renderers);
  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&end_game_button->ui_r->_super, ui_rs->_renderers);

  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&title->text_r->_super, ui_rs->_renderers); //!
  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&play_text->text_r->_super, ui_rs->_renderers);
  load_fail |= NULL == dAppend_LL(grRenderer_ptr)(&quit_text->text_r->_super, ui_rs->_renderers);

  load_fail |= NULL == dAppend_LL(geUI_Element_ptr)(&play_button->button_ui._super, ge_uim->_elements);
  load_fail |= NULL == dAppend_LL(geUI_Element_ptr)(&end_game_button->button_ui._super, ge_uim->_elements);

  if (load_fail) {
    goto end_scene_exception;
  }

  // ===
  // Add
  // ===

  // geAdd_Entity(title->_super, scene);
  // geAdd_Entity(play_text->_super, scene);
  // geAdd_Entity(quit_text->_super, scene);

  // load_fail |= NULL == geAdd_Entity(ui_camera->_super, scene);

  load_fail |= NULL == geAdd_System(rs->_super, scene);

  load_fail |= NULL == geAdd_System(ge_uim->_super, scene);
  load_fail |= NULL == geAdd_System(ui_rs->_super, scene);

  if (load_fail) {
    goto end_scene_exception;
  }

  goto no_exception;

  end_scene_exception :
    geEnd_Game(geGet_Active_Game());

  no_exception:

  return;
}
