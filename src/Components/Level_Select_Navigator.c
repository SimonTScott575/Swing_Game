#include "Level_Select_Navigator.h"

#include "../Scenes.h"
#include "../Scenes/Level_1.h"
#include "../Scenes/Level_2.h"
#include "../Scenes/Level_3.h"
#include "../Builders/Level_3_Basic_Build.h"

static float level_target_x_pos[LEVELS_COUNT] = {
  0,
  L2_MENU_POS,
  L3_MENU_POS
};
static float level_target_x_length[LEVELS_COUNT] = {
  L1_MAX_X_LENGTH + 2,
  L2_MAX_X_LENGTH + 10,
  L3_MAX_X_LENGTH
};

static void Set_Selected_Level(int level_num, Level_Select_Navigator* lsn);

Level_Select_Navigator* active_lsn = NULL;

Level_Select_Navigator* Create_Level_Select_Navigator(
  geButton_UI* next_level_b, grRenderer* next_level_r,
  geButton_UI* prev_level_b, grRenderer* prev_level_r,
  Level_Select_Camera_Controller* lscc
) {

  Level_Select_Navigator* lsn = malloc(sizeof(Level_Select_Navigator));

  if (active_lsn == NULL) {
    active_lsn = lsn;
  }

  lsn->next_level_b = next_level_b;
  lsn->next_level_r = next_level_r;
  lsn->prev_level_b = prev_level_b;
  lsn->prev_level_r = prev_level_r;

  lsn->lscc = lscc;
  // lsn->lscc->target_position = (mVector2f){{focused_level_num*60,0}};
  // lsn->lscc->x_length = level_target_x_length[focused_level_num] + 5;

  Set_Selected_Level(focused_level_num, lsn);

  lsn->_super = geCreate_Component();
  geSet_Sub_Component(lsn, NULL, Destroy_Level_Select_Navigator_Sub_Component, lsn->_super);

  return lsn;

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

  geSet_Next_Scene(level_select_menu, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_End_Game_Button(geUI_Element* uie) {

  geEnd_Game(geGet_Active_Game());

}

void On_Click_Main_Menu(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  focused_level_num = 0;

  geSet_Next_Scene(main_menu, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_Next_Level(geUI_Element* uie) {

  if (focused_level_num < LEVELS_COUNT-1) {
    Set_Selected_Level(++focused_level_num, active_lsn);
  }

  // active_lsn->lscc->target_position = (mVector2f){{focused_level_num*60,0}};
  // active_lsn->lscc->x_length = level_target_x_length[focused_level_num] + 5;

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
    active_lsn->prev_level_b->_super._super->is_active = false;
    active_lsn->prev_level_r->_super->is_active = false;

    active_lsn->next_level_b->_super._super->is_active = true;
    active_lsn->next_level_r->_super->is_active = true;
  } else if (level_num == LEVELS_COUNT-1) {
    active_lsn->next_level_b->_super._super->is_active = false;
    active_lsn->next_level_r->_super->is_active = false;

    active_lsn->prev_level_b->_super._super->is_active = true;
    active_lsn->prev_level_r->_super->is_active = true;
  } else {
    active_lsn->next_level_b->_super._super->is_active = true;
    active_lsn->next_level_r->_super->is_active = true;

    active_lsn->prev_level_b->_super._super->is_active = true;
    active_lsn->prev_level_r->_super->is_active = true;
  }

  active_lsn->lscc->target_position = (mVector2f){{level_target_x_pos[focused_level_num],0}};
  active_lsn->lscc->x_length = level_target_x_length[focused_level_num] + 5;

}
