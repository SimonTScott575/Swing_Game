#include "Level_Select_Menu.h"

#include "../Scenes.h"

#include "../Scenes/Level_Builder.h"
#include "../Scenes/Level_1.h"
#include "../Scenes/Level_2.h"
#include "../Scenes/Level_3.h"
#include "../Scenes/Level_4.h"
#include "../Scenes/Level_5.h"
#include "../Scenes/Level_6.h"
#include "../Scenes/Level_7.h"
#include "../Scenes/Level_8.h"

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

  Level_1_Builder l1_builder = Level_1_Builder_init(&l1_builder);
  l1_builder._super.as_scene = false;
  Level_2_Builder l2_builder = Level_2_Builder_init(&l2_builder);
  l2_builder._super.as_scene = false;
  Level_3_Builder l3_builder = Level_3_Builder_init(&l3_builder);
  l3_builder._super.as_scene = false;
  Level_4_Builder l4_builder = Level_4_Builder_init(&l4_builder);
  l4_builder._super.as_scene = false;
  Level_5_Builder l5_builder = Level_5_Builder_init(&l5_builder);
  l5_builder._super.as_scene = false;
  Level_6_Builder l6_builder = Level_6_Builder_init(&l6_builder);
  l6_builder._super.as_scene = false;
  Level_7_Builder l7_builder = Level_7_Builder_init(&l7_builder);
  l7_builder._super.as_scene = false;
  Level_8_Builder l8_builder = Level_8_Builder_init(&l8_builder);
  l8_builder._super.as_scene = false;

  // ---
  // ECS
  // ---

  Level_Select_Camera* lsc = Create_Level_Select_Camera(40);
  
  Build_Level_Basics_Load(g_level_specs[0].offset_x, &l1_builder._super);
  Build_Level_Basics_Load(g_level_specs[1].offset_x, &l7_builder._super);
  Build_Level_Basics_Load(g_level_specs[2].offset_x, &l2_builder._super);
  Build_Level_Basics_Load(g_level_specs[3].offset_x, &l3_builder._super);
  Build_Level_Basics_Load(g_level_specs[4].offset_x, &l4_builder._super);
  Build_Level_Basics_Load(g_level_specs[5].offset_x, &l5_builder._super);
  Build_Level_Basics_Load(g_level_specs[6].offset_x, &l6_builder._super);
  Build_Level_Basics_Load(g_level_specs[7].offset_x, &l8_builder._super);

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

  Menu_Text* locked_text = Create_Menu_Text("BEAT PAR TO CONTINUE", NULL, 0, 0,0,0, 0.5);
  locked_text->text_r->text->alignment = GR_ALIGN_CENTRE;

  Level_Selector* level_selector = Create_Level_Selector(
    next_button->_super,
    prev_button->_super,
    play_level_button->_super,
    play_level_text->_super,
    locked_text->text_r->_super->_super->_entity,
    lsc->lscc
  );

  grRendering_System2D* ui_rs = grCreate_Rendering_System2D(ui_camera->camera);

  geUI_Manager* ge_uim = geCreate_UI_Manager(ui_camera->camera);

  // ---
  // Set
  // ---

  Build_Level_Basics_Set(rs, &l1_builder._super);
  Build_Level_Basics_Set(rs, &l2_builder._super);
  Build_Level_Basics_Set(rs, &l3_builder._super);
  Build_Level_Basics_Set(rs, &l4_builder._super);
  Build_Level_Basics_Set(rs, &l5_builder._super);
  Build_Level_Basics_Set(rs, &l6_builder._super);
  Build_Level_Basics_Set(rs, &l7_builder._super);
  Build_Level_Basics_Set(rs, &l8_builder._super);

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

  dAppend_LL(grRenderer_ptr)(locked_text->text_r->_super, ui_rs->_renderers);

  // ---
  // Add
  // ---

  Build_Level_Basics_Add(scene, &l1_builder._super);
  Build_Level_Basics_Add(scene, &l2_builder._super);
  Build_Level_Basics_Add(scene, &l3_builder._super);
  Build_Level_Basics_Add(scene, &l4_builder._super);
  Build_Level_Basics_Add(scene, &l5_builder._super);
  Build_Level_Basics_Add(scene, &l6_builder._super);
  Build_Level_Basics_Add(scene, &l7_builder._super);
  Build_Level_Basics_Add(scene, &l8_builder._super);

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

  geAdd_Entity(locked_text->_super, scene);

  geAdd_System(rs->_super, scene);

  geAdd_System(ge_uim->_super, scene);
  geAdd_System(ui_rs->_super, scene);

}
