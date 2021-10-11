#include "End_Level_Menu_Build.h"

void Load_Entities_End_Level_Menu_Build(Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller, End_Level_Menu_Build* build) {

  build->uic = Create_UI_Camera();

  build->cd_menu_text = Create_Menu_Text_With_Resolution("3", NULL, 0,0,0,-0.15, 1.5, 512);

  build->back_mt       = Create_Menu_Text("MENU", NULL,   -1,-1,  0.4,0.15, 0.6);
  build->restart_mt    = Create_Menu_Text("RESTART", NULL, 0,-1,  0,  0.15, 0.6);
  build->next_level_mt = Create_Menu_Text("NEXT", NULL,    1,-1, -0.4,0.15, 0.6);

  build->back_b       = Create_Menu_Button( -1,-1,  0.4,0.2, 0.5,0.2, "../Resources/Textures/clear_1.png", On_Click_Back_Button);
  build->restart_b    = Create_Menu_Button(  0,-1,  0,0.2,   0.7,0.2, "../Resources/Textures/clear_1.png", On_Click_Restart_Button);
  build->next_level_b = Create_Menu_Button(  1,-1, -0.4,0.2, 0.5,0.2, "../Resources/Textures/clear_1.png", On_Click_Next_Level_Button);

  build->m_uim = Create_UI_Manager(
    pc, clock, player_controller,
    build->cd_menu_text->text_r,

    (geEntity*[4]){build->back_b->_super, build->restart_b->_super, build->back_mt->_super, build->restart_mt->_super},
    (geEntity*[2]){build->next_level_b->_super, build->next_level_mt->_super}

  );

}

void Load_Systems_End_Level_Menu_Build(End_Level_Menu_Build* build) {

  UI_Camera* uic = build->uic;

  build->uim = geCreate_UI_Manager(uic->camera);
  build->rs_ui = grCreate_Rendering_System2D(uic->camera);

}

void Set_End_Level_Menu_Build(End_Level_Menu_Build* build) {

  Menu_Text* cd_menu_text = build->cd_menu_text;
  Menu_Button* back_b = build->back_b;
  Menu_Button* restart_b = build->restart_b;
  Menu_Button* next_level_b = build->next_level_b;
  Level_Transitioner* lt = build->m_uim->lt;

  dAppend_LL(geUI_Element_ptr)(&restart_b->button_ui->_super,    build->uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&next_level_b->button_ui->_super, build->uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&back_b->button_ui->_super,       build->uim->_elements);

  dAppend_LL(grRenderer_ptr)(restart_b->ui_r->_super,    build->rs_ui->_renderers);
  dAppend_LL(grRenderer_ptr)(next_level_b->ui_r->_super, build->rs_ui->_renderers);
  dAppend_LL(grRenderer_ptr)(back_b->ui_r->_super,       build->rs_ui->_renderers);

  dAppend_LL(grRenderer_ptr)(build->back_mt->text_r->_super, build->rs_ui->_renderers);
  dAppend_LL(grRenderer_ptr)(build->restart_mt->text_r->_super, build->rs_ui->_renderers);
  dAppend_LL(grRenderer_ptr)(build->next_level_mt->text_r->_super, build->rs_ui->_renderers);

  dAppend_LL(grRenderer_ptr)(lt->cd_text_r->_super, build->rs_ui->_renderers);

}

void Add_Entities_End_Level_Menu_Build(geScene* scene, End_Level_Menu_Build* build) {

  geAdd_Entity(build->cd_menu_text->_super, scene);

  geAdd_Entity(build->back_mt->_super, scene);
  geAdd_Entity(build->restart_mt->_super, scene);
  geAdd_Entity(build->next_level_mt->_super, scene);

  geAdd_Entity(build->back_b->_super, scene);
  geAdd_Entity(build->restart_b->_super, scene);
  geAdd_Entity(build->next_level_b->_super, scene);

  geAdd_Entity(build->uic->_super, scene);
  geAdd_Entity(build->m_uim->_super, scene);

}

void Add_Systems_End_Level_Menu_Build(geScene* scene, End_Level_Menu_Build* build) {

  geAdd_System(build->uim->_super, scene);
  geAdd_System(build->rs_ui->_super, scene);

}
