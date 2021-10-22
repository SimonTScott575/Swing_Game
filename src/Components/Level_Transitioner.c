#include "Level_Transitioner.h"

#include <math.h>
#include <string.h>

#include "../Scenes.h"

#define INTRO_TIME2 0.5
#define INTRO_TIME 0.8
#define INTRO_TIME3 0.2
#define CD_TIME 3

void Level_Transitioner_ctor(
  Level_Transitioner* self,
  Portal_Catcher* pc, Timer_Clock* clock, Player_Controller* player_controller,
  grText_Renderer* cd_text_r,
  geEntity** end_ui1_arr, // restart and back : button/text entities
  geEntity** end_ui2_arr // next level : button/text entities
) {

  *self = (Level_Transitioner){

    .pc = pc,
    .clock = clock,
    .player_controller = player_controller,

    .cd_text = cd_text_r->text,
    .cd_text_r = cd_text_r,

  };

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Level_Transitioner, NULL, &self->_super);

  memcpy(self->end_ui1_arr, end_ui1_arr, END_UI1_LENGTH*sizeof(geEntity*));
  memcpy(self->end_ui2_arr, end_ui2_arr, END_UI2_LENGTH*sizeof(geEntity*));
  for (int i = 0; i < END_UI1_LENGTH; i++) {
    self->end_ui1_arr[i]->is_active = false;
  }
  for (int i = 0; i < END_UI2_LENGTH; i++) {
    self->end_ui2_arr[i]->is_active = false;
  }

  self->level_start_time = 0;
  self->cd_first_frame = 0;
  self->cd_over = 0;

  self->cd_text_r->_super._super.is_active = false;
  self->cd_text->alignment = GR_ALIGN_CENTRE;

}

void Update_Level_Transitioner(geComponent* component) {

  Level_Transitioner* lt = component->_sub;

  if (lt->cd_first_frame == 0) {
    lt->level_start_time = geGet_Active_Game()->time;
    lt->cd_first_frame += 1;
  }

  float level_time = geGet_Active_Game()->time - lt->level_start_time;

  if (level_time < INTRO_TIME2) {
    lt->player_controller->rb->frame->scale.i[0]
      = lt->player_controller->rb->frame->scale.i[1] = 0;
  }
  else
  if (INTRO_TIME2 < level_time && level_time < INTRO_TIME2+INTRO_TIME) {

    lt->player_controller->rb->frame->scale.i[0]
      = lt->player_controller->rb->frame->scale.i[1]
      = ( 2*exp(-0.693*(level_time-INTRO_TIME2)/INTRO_TIME) ) * 0.5*sin( 5/4.0 * 2*M_PI * (level_time-INTRO_TIME2)/INTRO_TIME - M_PI/2 ) + 1;
      // = (-(level_time-INTRO_TIME2)/INTRO_TIME + 2) * 0.5*sin( 5/4.0 * 2*M_PI * (level_time-INTRO_TIME2)/INTRO_TIME - M_PI/2 ) + 1;

  }
  else
  if (INTRO_TIME2+INTRO_TIME+INTRO_TIME3 < level_time && level_time < CD_TIME+INTRO_TIME+INTRO_TIME2+INTRO_TIME3) {

    lt->player_controller->rb->frame->scale.i[0]
      = lt->player_controller->rb->frame->scale.i[1]
      = 1;

    int cd = 1 + (INTRO_TIME2+INTRO_TIME+CD_TIME - level_time);
    if (cd == 0) { goto EXIT_CD; }
    char level_time_s[100];
    sprintf(level_time_s, "%d", cd);

    grSet_Text_Contents(level_time_s, lt->cd_text);
    lt->cd_text_r->_super._super.is_active = true;

  }
  else
  if (   CD_TIME+INTRO_TIME+INTRO_TIME2+INTRO_TIME3 < level_time
      && !lt->cd_over) {

    lt->player_controller->rb->_super.is_active = true;

    lt->clock->time_start = geGet_Active_Game()->time;
    lt->clock->is_started = true;

    lt->cd_text_r->_super._super.is_active = false;

    lt->cd_over = 1;
  } EXIT_CD:

  if (lt->pc->is_caught) {

    if ( lt->clock->timer_val < best_times[focused_level_num] || best_times[focused_level_num] < 0 ) {
      best_times[focused_level_num] = lt->clock->timer_val;
    }

    for (int i = 0; i < END_UI1_LENGTH; i++) {
      lt->end_ui1_arr[i]->is_active = true;
    }

    if (   best_times[focused_level_num] < par_times[focused_level_num]
        && focused_level_num < LEVELS_COUNT-1 ) {

      for (int i = 0; i < END_UI2_LENGTH; i++) {
        lt->end_ui2_arr[i]->is_active = true;
      }

    }

    lt->clock->is_ended = true;
  }

  if (geKey_Down(geGet_Active_Game(), GE_KB_ESCAPE)) {
    geSet_Next_Scene(g_level_select_menu, geGet_Active_Game());
    geEnd_Scene(geGet_Active_Game());
  }

}

void On_Click_Back_Button(geUI_Element* uie) {

  geGame* active_game = geGet_Active_Game();

  geSet_Next_Scene(g_level_select_menu, active_game);
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
