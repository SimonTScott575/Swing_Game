#include "Level_Select_Navigator.h"

static void Set_Selected_Level(int level_num, Level_Select_Navigator* lsn);

Level_Select_Navigator* active_lsn = NULL;

void Level_Select_Navigator_ctor(
  Level_Select_Navigator* self,
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* play_level_text_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc
) {

  if (active_lsn == NULL) {
    active_lsn = self;
  }

  self->next_level_e = next_level_e;
  self->prev_level_e = prev_level_e;
  self->play_level_e = play_level_e;
  self->play_level_text_e = play_level_text_e;

  self->locked_e = locked_e;

  self->lscc = lscc;
  // lsn->lscc->target_position = (mVector2f){{focused_level_num*60,0}};
  // lsn->lscc->x_length = level_target_x_length[focused_level_num] + 5;

  Set_Selected_Level(focused_level_num, self);

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self,
                      Update_Level_Select_Navigator_Sub_Component,
                      Level_Select_Navigator_Sub_Component_dtor,
                      &self->_super);

}

void Update_Level_Select_Navigator_Sub_Component(geComponent* component) {

  Level_Select_Navigator* lsn = component->_sub;

  if (focused_level_num > 0) {

    if (   best_times[focused_level_num-1] > par_times[focused_level_num-1]
        || best_times[focused_level_num-1] < 0 ) {
      lsn->play_level_e->is_active = false;
      lsn->play_level_text_e->is_active = false;
      lsn->locked_e->is_active = true;
    } else {
      lsn->play_level_e->is_active = true;
      lsn->play_level_text_e->is_active = true;
      lsn->locked_e->is_active = false;
    }

  } else {
    lsn->play_level_e->is_active = true;
    lsn->play_level_text_e->is_active = true;
    lsn->locked_e->is_active = false;
  }

}

void Level_Select_Navigator_Sub_Component_dtor(geComponent* component) {

  Level_Select_Navigator* lsn = component->_sub;

  if (active_lsn == lsn) {
    active_lsn = NULL;
  }

}

void On_Click_Play_Button(geUI_Element* uie) { //? component ?

  geGame* active_game = geGet_Active_Game();

  focused_level_num = 0;

  geSet_Next_Scene(g_level_select_menu, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_End_Game_Button(geUI_Element* uie) {

  geEnd_Game(geGet_Active_Game());

}

void On_Click_Main_Menu(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  focused_level_num = 0;

  geSet_Next_Scene(g_main_menu, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_Next_Level(geUI_Element* uie) {

  if (focused_level_num < LEVELS_COUNT-1) {
    Set_Selected_Level(++focused_level_num, active_lsn);
  }

}

void On_Click_Prev_Level(geUI_Element* uie) {

  if (focused_level_num > 0) {
    Set_Selected_Level(--focused_level_num, active_lsn);
  }

}

void On_Click_Play_Level(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  geSet_Next_Scene(level_order[focused_level_num], active_game);

  geEnd_Scene(active_game);

}

static void Set_Selected_Level(int level_num, Level_Select_Navigator* lsn) {

  geScene* selected_level = level_order[level_num];

  if (level_num == 0) {
    active_lsn->prev_level_e->is_active = false;
    active_lsn->next_level_e->is_active = true;
  } else if (level_num == LEVELS_COUNT-1) {
    active_lsn->next_level_e->is_active = false;
    active_lsn->prev_level_e->is_active = true;
  } else {
    active_lsn->next_level_e->is_active = true;
    active_lsn->prev_level_e->is_active = true;
  }

  active_lsn->lscc->target_position = (mVector2f){{
    g_level_specs[focused_level_num].menu_camera_x_pos,
    g_level_specs[focused_level_num].menu_camera_y_pos
  }};
  active_lsn->lscc->x_length = g_level_specs[focused_level_num].menu_camera_x_length;

}
