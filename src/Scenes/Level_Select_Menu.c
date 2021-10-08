#include "Level_Select_Menu.h"

#include "../Scenes.h"

#include "../Builders/Level_1_Surfaces_Build.h"
#include "../Builders/Level_2_Basic_Build.h"
#include "../Builders/Level_3_Basic_Build.h"

#include "../Entities/UI_Camera.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Level_Selector.h"
#include "../Entities/Level_Select_Camera.h"
#include "../Entities/Hook_Surface.h"
#include "../Entities/Background.h"
#include "../Entities/Menu_Text.h"

#include "../Components/Display_Time.h"
#include "../Components/Level_Title.h"

void Load_Level_Select_Menu(geScene* scene) {

  Level_1_Surfaces_Build level_1_surfaces_build = Level_1_Surfaces_Build_init(0);
  Level_2_Basic_Build level_2_basic_build = Level_2_Basic_Build_init(0);
  Level_3_Basic_Build level_3_basic_build = Level_3_Basic_Build_init(0);

  // ---
  // ECS
  // ---

  Load_Entity_Player_Level_1_Surfaces_Build(L1_MENU_POS, &level_1_surfaces_build);
  Load_Entity_Player_Level_2_Basic_Build(&level_2_basic_build);
  Load_Entity_Player_Level_3_Basic_Build(&level_3_basic_build);

  Level_Select_Camera* lsc = Create_Level_Select_Camera(40);

  Load_Entities_Level_1_Surfaces_Build(L1_MENU_POS, lsc->camera2D->frame, NULL, &level_1_surfaces_build);
  Load_Entities_Level_2_Basic_Build(L2_MENU_POS, lsc->camera2D->frame, &level_2_basic_build);
  Load_Entities_Level_3_Basic_Build(L3_MENU_POS, lsc->camera2D->frame, &level_3_basic_build);

  grRendering_System2D* rs = grCreate_Rendering_System2D(lsc->camera2D);

  UI_Camera* ui_camera = Create_UI_Camera();

  Menu_Button* prev_button       = Create_Menu_Button(-1,0, 0.15,0, 0.1,0.3, "../Resources/Textures/left_arrow_white_256.png", On_Click_Prev_Level);
  Menu_Button* next_button       = Create_Menu_Button(1,0, -0.15,0, 0.1,0.3, "../Resources/Textures/right_arrow_white_256.png", On_Click_Next_Level);
  Menu_Button* play_level_button = Create_Menu_Button(0,-1, 0,0.2, 0.5,0.2, "../Resources/Textures/clear_1.png", On_Click_Play_Level);
  Menu_Button* main_menu_button  = Create_Menu_Button(-1,-1, 0.4,0.2, 0.5,0.2, "../Resources/Textures/clear_1.png", On_Click_Main_Menu);

  Menu_Text* play_level_text = Create_Menu_Text("START", NULL, 0,-1,  0,  0.15,  0.6);
  Menu_Text* main_menu_text  = Create_Menu_Text("MENU", NULL, -1,-1,  0.4,0.15,  0.6);

  Menu_Text* level_name_text = Create_Menu_Text("LEVEL_TITLE", "../Resources/Fonts/Fira/FiraSans-HeavyItalic.ttf",-1, 1, 0.1,-0.25, 1);
  Level_Title* level_title = Create_Level_Title(-15, level_name_text->text_r);
  geAdd_Component(level_title->_super, level_name_text->_super);

  level_name_text->text_r->text->alignment
    = GR_ALIGN_LEFT;


  Menu_Text* best_time_text = Create_Menu_Text("BEST TIME:", NULL, 1, 1,-0.1,-0.25, 0.6);
  Menu_Text* par_time_text  = Create_Menu_Text("PAR:",       NULL, 1,-1,-0.1, 0.35, 0.6);
  Display_Time* dt_par = Create_Display_Time("PAR: ", par_times, par_time_text->text_r, 15);
  geAdd_Component(dt_par->_super, par_time_text->_super);
  Display_Time* dt_best = Create_Display_Time("BEST: ", best_times, best_time_text->text_r, 15);
  geAdd_Component(dt_best->_super, best_time_text->_super);

  best_time_text->text_r->text->alignment
    = par_time_text->text_r->text->alignment
    = GR_ALIGN_RIGHT;

  Level_Selector* level_selector = Create_Level_Selector(
    next_button->button_ui, next_button->ui_r->_super,
    prev_button->button_ui, prev_button->ui_r->_super,
    play_level_button->button_ui, play_level_text->text_r,
    lsc->lscc
  );

  grRendering_System2D* ui_rs = grCreate_Rendering_System2D(ui_camera->camera);

  geUI_Manager* ge_uim = geCreate_UI_Manager(ui_camera->camera);

  // ---
  // Set
  // ---

  Set_Level_1_Surfaces_Build(lsc->camera2D, rs, NULL, &level_1_surfaces_build);
  Set_Level_2_Basic_Build(lsc->camera2D, rs, NULL, &level_2_basic_build);
  Set_Level_3_Basic_Build(lsc->camera2D, rs, NULL, &level_3_basic_build);

  lsc->lscc->rs = rs;

  dAppend_LL(grRenderer_ptr)(level_name_text->text_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(best_time_text->text_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(par_time_text->text_r->_super, ui_rs->_renderers);

  dAppend_LL(grRenderer_ptr)(prev_button->ui_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(next_button->ui_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(play_level_button->ui_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(main_menu_button->ui_r->_super, ui_rs->_renderers);

  dAppend_LL(grRenderer_ptr)(play_level_text->text_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(main_menu_text->text_r->_super, ui_rs->_renderers);

  dAppend_LL(geUI_Element_ptr)(&prev_button->button_ui->_super, ge_uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&next_button->button_ui->_super, ge_uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&play_level_button->button_ui->_super, ge_uim->_elements);
  dAppend_LL(geUI_Element_ptr)(&main_menu_button->button_ui->_super, ge_uim->_elements);

  // ---
  // Add
  // ---

  Add_Entities_Level_1_Surfaces_Build(scene, &level_1_surfaces_build);
  Add_Entities_Level_2_Basic_Build(scene, &level_2_basic_build);
  Add_Entities_Level_3_Basic_Build(scene, &level_3_basic_build);

  geAdd_Entity(lsc->_super, scene);

  geAdd_Entity(ui_camera->_super, scene);
  geAdd_Entity(prev_button->_super, scene);
  geAdd_Entity(next_button->_super, scene);
  geAdd_Entity(play_level_button->_super, scene);
  geAdd_Entity(main_menu_button->_super, scene);
  geAdd_Entity(level_selector->_super, scene);

  geAdd_Entity(play_level_text->_super, scene);
  geAdd_Entity(main_menu_text->_super, scene);

  geAdd_Entity(level_name_text->_super, scene);
  geAdd_Entity(best_time_text->_super, scene);
  geAdd_Entity(par_time_text->_super, scene);

  geAdd_System(rs->_super, scene);

  geAdd_System(ge_uim->_super, scene);
  geAdd_System(ui_rs->_super, scene);

}
