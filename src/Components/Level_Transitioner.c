#include "Level_Transitioner.h"

#include "../Scenes.h"

Level_Transitioner* Create_Level_Transitioner(
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText* cd_text,           grText_Renderer* cd_text_r,
  geButton_UI* back_b,       grRenderer* back_r,
  geButton_UI* restart_b,    grRenderer* restart_r,
  geButton_UI* next_level_b, grRenderer* next_level_r,
  grText_Renderer* back_tr, grText_Renderer* restart_tr, grText_Renderer* next_level_tr
) {

  Level_Transitioner* lt = malloc(sizeof(Level_Transitioner));

  *lt = (Level_Transitioner){

    ._super = geCreate_Component(),

    .pc = pc,
    .clock = clock,
    .player_controller = player_controller,

    .cd_text = cd_text,
    .cd_text_r = cd_text_r,

    .back_b = back_b,
    .back_r = back_r,

    .restart_b = restart_b,
    .restart_r = restart_r,

    .next_level_b = next_level_b,
    .next_level_r = next_level_r,

    .back_tr = back_tr,
    .restart_tr = restart_tr,
    .next_level_tr = next_level_tr

  };

  geSet_Sub_Component(lt, Update_Level_Transitioner, Destroy_Level_Transitioner_Sub_Component, lt->_super);

  lt->back_b->_super._super->is_active = false;
  lt->back_r->_super->is_active = false;
  lt->back_tr->_super->_super->is_active = false;

  lt->restart_b->_super._super->is_active = false;
  lt->restart_r->_super->is_active = false;
  lt->restart_tr->_super->_super->is_active = false;

  lt->next_level_b->_super._super->is_active = false;
  lt->next_level_r->_super->is_active = false;
  lt->next_level_tr->_super->_super->is_active = false;

  lt->cd_over = 0;

  lt->cd_text->alignment = GR_ALIGN_CENTRE;

  return lt;

}

void Update_Level_Transitioner(geComponent* component) {

  Level_Transitioner* lt = component->_sub;

  float level_time = geGet_Active_Game()->time - lt->clock->time_start;
  int cd = 3 - (int)level_time;
  char level_time_s[100];
  sprintf(level_time_s, "%d", cd);

  if (level_time < 3) {

    grSet_Text_Contents(level_time_s, lt->cd_text);
  } else if (!lt->cd_over) {

    lt->player_controller->rb->_super->is_active = true;

    lt->clock->time_start = geGet_Active_Game()->time;
    lt->clock->is_started = true;

    lt->cd_text_r->_super->_super->is_active = false;

    lt->cd_over = 1;
  }

  if (lt->pc->is_caught) {
    lt->back_r->_super->is_active = true;
    lt->back_b->_super._super->is_active = true;
    lt->back_tr->_super->_super->is_active = true;

    lt->restart_r->_super->is_active = true;
    lt->restart_b->_super._super->is_active = true;
    lt->restart_tr->_super->_super->is_active = true;

    if (focused_level_num < LEVELS_COUNT-1) {
      lt->next_level_r->_super->is_active = true;
      lt->next_level_b->_super._super->is_active = true;
      lt->next_level_tr->_super->_super->is_active = true;
    }

    if ( lt->clock->timer_val < best_times[focused_level_num] || best_times[focused_level_num] < 0 ) {
      best_times[focused_level_num] = lt->clock->timer_val;
    }

    lt->clock->is_ended = true;
  }

}

void Destroy_Level_Transitioner_Sub_Component(geComponent* component) {

  Level_Transitioner* lt = component->_sub;

  free(lt);

}

void On_Click_Back_Button(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  geSet_Next_Scene(level_select_menu, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_Restart_Button(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  geSet_Next_Scene(active_game->_active_scene, active_game);
  geEnd_Scene(geGet_Active_Game());

}

void On_Click_Next_Level_Button(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  if (focused_level_num < LEVELS_COUNT-1) {
    geSet_Next_Scene(level_order[++focused_level_num], active_game);

    geEnd_Scene(active_game);

  }

}
