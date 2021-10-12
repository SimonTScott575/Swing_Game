#include "Level_Select_Navigator.h"

#include "../Level_Spec.h"

static void Set_Selected_Level(int level_num, Level_Select_Navigator* lsn);

Level_Select_Navigator* active_lsn = NULL;

Level_Select_Navigator* Create_Level_Select_Navigator(
  geEntity* next_level_e,
  geEntity* prev_level_e,
  geEntity* play_level_e,
  geEntity* locked_e,
  Level_Select_Camera_Controller* lscc
) {

  Level_Select_Navigator* lsn = malloc(sizeof(Level_Select_Navigator));

  if (active_lsn == NULL) {
    active_lsn = lsn;
  }

  lsn->next_level_e = next_level_e;
  lsn->prev_level_e = prev_level_e;
  lsn->play_level_e = play_level_e;

  lsn->locked_e = locked_e;

  lsn->lscc = lscc;
  // lsn->lscc->target_position = (mVector2f){{focused_level_num*60,0}};
  // lsn->lscc->x_length = level_target_x_length[focused_level_num] + 5;

  Set_Selected_Level(focused_level_num, lsn);

  lsn->_super = geCreate_Component();
  geSet_Sub_Component(lsn,
                      Update_Level_Select_Navigator_Sub_Component,
                      Destroy_Level_Select_Navigator_Sub_Component,
                      lsn->_super);

  return lsn;

}

void Update_Level_Select_Navigator_Sub_Component(geComponent* component) {

  Level_Select_Navigator* lsn = component->_sub;

  if (focused_level_num > 0) {

    if (   best_times[focused_level_num-1] > par_times[focused_level_num-1]
        || best_times[focused_level_num-1] < 0 ) {
      lsn->play_level_e->is_active = false;
      lsn->play_level_e->is_active = false;
      lsn->locked_e->is_active = true;
    } else {
      lsn->play_level_e->is_active = true;
      lsn->play_level_e->is_active = true;
      lsn->locked_e->is_active = false;
    }

  } else {
    lsn->play_level_e->is_active = true;
    lsn->play_level_e->is_active = true;
    lsn->locked_e->is_active = false;
  }

}

void Destroy_Level_Select_Navigator_Sub_Component(geComponent* component) {

  Level_Select_Navigator* lsn = component->_sub;

  if (active_lsn == lsn) {
    active_lsn = NULL;
  }

  free(lsn);

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
