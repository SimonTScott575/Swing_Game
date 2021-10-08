#include "Level_UI_Build.h"

void Load_Entities_Level_UI_Build(Level_UI_Build* build) {

  //
  build->ui_camera = Create_UI_Camera();

  build->timer_sec_mt = Create_Menu_Text("0", NULL,    1,1,-0.4,-0.2, 0.8);
  build->timer_msec_mt = Create_Menu_Text(".00", NULL, 1,1,-0.4,-0.2, 0.8);

  build->score_num_mt = Create_Menu_Text("", NULL, -1,1, 0.25,-0.2, 0.8);
  build->score_den_mt = Create_Menu_Text("", NULL, -1,1, 0.25,-0.2, 0.8);

  build->timer = Create_Timer(build->timer_sec_mt->text, build->timer_msec_mt->text);
  build->score = Create_Score(build->score_num_mt->text, build->score_num_mt->text_r,
                              build->score_den_mt->text, build->score_den_mt->text_r);

}

void Load_Systems_Level_UI_Build(Level_UI_Build* build) {

  build->ui_rs = grCreate_Rendering_System2D(build->ui_camera->camera);
  build->ge_uim = geCreate_UI_Manager(build->ui_camera->camera);

}

void Set_Level_UI_Build(Level_UI_Build* build) {

  grRendering_System2D* ui_rs = build->ui_rs;

  dAppend_LL(grRenderer_ptr)(build->timer_sec_mt->text_r->_super,  ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->timer_msec_mt->text_r->_super, ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->score_num_mt->text_r->_super,  ui_rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->score_den_mt->text_r->_super,  ui_rs->_renderers);

}

void Add_Entities_Level_UI_Build(geScene* scene, Level_UI_Build* build) {

  geAdd_Entity(build->ui_camera->_super, scene);
  geAdd_Entity(build->score_num_mt->_super, scene);
  geAdd_Entity(build->score_den_mt->_super, scene);
  geAdd_Entity(build->timer_sec_mt->_super, scene);
  geAdd_Entity(build->timer_msec_mt->_super, scene);
  geAdd_Entity(build->timer->_super, scene);
  geAdd_Entity(build->score->_super, scene);

}

void Add_Systems_Level_UI_Build(geScene* scene, Level_UI_Build* build) {

  geAdd_System(build->ge_uim->_super, scene);
  geAdd_System(build->ui_rs->_super, scene);

}
