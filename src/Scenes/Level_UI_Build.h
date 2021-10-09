#ifndef LEVEL_UI_BUILD_H
#define LEVEL_UI_BUILD_H

#include <Game_Engine/Game_Engine.h>

#include "../Entities/UI_Camera.h"
#include "../Entities/Menu_Text.h"
#include "../Entities/Timer.h"
#include "../Entities/Score.h"

typedef
struct Level_UI_Build {

  UI_Camera* ui_camera;
  Menu_Text* score_num_mt;
  Menu_Text* score_den_mt;
  Menu_Text* timer_sec_mt;
  Menu_Text* timer_msec_mt;
  Timer* timer;
  Score* score;
  grRendering_System2D* ui_rs;
  geUI_Manager* ge_uim;

} Level_UI_Build;

void Load_Entities_Level_UI_Build(Level_UI_Build* level_ui_build);
void Load_Systems_Level_UI_Build(Level_UI_Build* level_ui_build);

void Set_Level_UI_Build(Level_UI_Build* level_ui_build);

void Add_Entities_Level_UI_Build(geScene* scene, Level_UI_Build* level_ui_build);
void Add_Systems_Level_UI_Build(geScene* scene, Level_UI_Build* level_ui_build);

#endif
