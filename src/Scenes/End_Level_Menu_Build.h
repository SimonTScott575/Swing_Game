#ifndef LOAD_IN_LEVEL_MENU_H
#define LOAD_IN_LEVEL_MENU_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/Menu_Text.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"

typedef
struct End_Level_Menu_Build {

  UI_Camera* uic;

  Menu_Text* cd_menu_text;

  Menu_Text* back_mt;
  Menu_Text* restart_mt;
  Menu_Text* next_level_mt;

  Menu_Button* back_b;
  Menu_Button* restart_b;
  Menu_Button* next_level_b;

  UI_Manager* m_uim;

  geUI_Manager* uim;
  grRendering_System2D* rs_ui;

} End_Level_Menu_Build;

void Load_Entities_End_Level_Menu_Build(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  geScene* scene,
  End_Level_Menu_Build* build
);
void Load_Systems_End_Level_Menu_Build(End_Level_Menu_Build* build);
void Set_End_Level_Menu_Build(End_Level_Menu_Build* build);
void Add_Entities_End_Level_Menu_Build(geScene* scene, End_Level_Menu_Build* build);
void Add_Systems_End_Level_Menu_Build(geScene* scene, End_Level_Menu_Build* build);

#endif
