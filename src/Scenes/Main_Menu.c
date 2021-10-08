#include "Main_Menu.h"

#include "../Entities/UI_Camera.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Menu_Camera.h"
#include "../Entities/Background.h"
#include "../Entities/Menu_Text.h"
//TODO: should have better place to store Play and End_Game on click callback
#include "../Components/Level_Select_Navigator.h"

void Load_Main_Menu(geScene* scene) {

  // ========
  // Load ECS
  // ========

  // --------
  // Entities
  // --------

  Menu_Text* title = Create_Menu_Text("SWING", "../Resources/Fonts/Fira/FiraSans-HeavyItalic.ttf", 0,0, 0,0.4, 1.5);
  Menu_Text* play_text = Create_Menu_Text("PLAY", NULL, 0,0, 0,0.04, 0.7);
  Menu_Text* quit_text = Create_Menu_Text("QUIT", NULL, 0,0, 0,-0.21, 0.7);

  Menu_Camera* menu_camera = Create_Menu_Camera(50);

  Background* bg = Create_Background(50,50);

  grRendering_System2D* rs = grCreate_Rendering_System2D(menu_camera->camera2D);

  UI_Camera* ui_camera = Create_UI_Camera();

  Menu_Button* play_button = Create_Menu_Button(0,0, 0,0.1, 1,0.2, "../Resources/Textures/square_orange_256.png", On_Click_Play_Button);
  Menu_Button* end_game_button = Create_Menu_Button(0,0, 0,-0.15, 1,0.2, "../Resources/Textures/square_orange_256.png", On_Click_End_Game_Button);

  // -------
  // Systems
  // -------

  grRendering_System2D* ui_rs = grCreate_Rendering_System2D(ui_camera->camera);

  geUI_Manager* ge_uim = geCreate_UI_Manager(ui_camera->camera);

  // ===
  // Set
  // ===

  dAppend_LL(grRenderer_ptr)(bg->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(play_button->ui_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(end_game_button->ui_r->_super, ui_rs->_renderers);

  dAppend_LL(grRenderer_ptr)(title->text_r->_super, ui_rs->_renderers); //!
  dAppend_LL(grRenderer_ptr)(play_text->text_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(quit_text->text_r->_super, ui_rs->_renderers);

  dAppend_LL(geUI_Element_ptr)(&play_button->button_ui->_super, ge_uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&end_game_button->button_ui->_super, ge_uim->_elements);

  // ===
  // Add
  // ===

  geAdd_Entity(menu_camera->_super, scene);
  geAdd_Entity(bg->_super, scene);

  geAdd_Entity(ui_camera->_super, scene);
  geAdd_Entity(play_button->_super, scene);
  geAdd_Entity(end_game_button->_super, scene);

  geAdd_Entity(title->_super, scene);
  geAdd_Entity(play_text->_super, scene);
  geAdd_Entity(quit_text->_super, scene);

  geAdd_System(rs->_super, scene);

  geAdd_System(ge_uim->_super, scene);
  geAdd_System(ui_rs->_super, scene);

}
