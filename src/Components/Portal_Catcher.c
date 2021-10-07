#include "Portal_Catcher.h"

#include <stdio.h>

#include "../Layers.h"

#include "Gem_Controller.h"

mVector2f g_portal_pos = mVector2f_ZERO;
int g_portal_catches_player = 0;
float g_portal_catch_time = 0;

Portal_Catcher* Create_Portal_Catcher(float radius, phRigid_Body2D* rb) {

  Portal_Catcher* pc = malloc(sizeof(Portal_Catcher));

  phSave_Collider_Collisions(rb->collider, pc->collisions, 10);

  g_portal_catches_player = 0;
  g_portal_catch_time = 0;

  *pc = (Portal_Catcher){

    .radius = radius,
    .is_caught = false,

    .collider = rb->collider,
    .rb = rb

  };

  pc->_super = geCreate_Component();
  geSet_Sub_Component(pc, Update_Portal_Catcher, Destroy_Portal_Catcher_Sub_Component, pc->_super);

  return pc;

};

void Update_Portal_Catcher(geComponent* component) {

  Portal_Catcher* pc = component->_sub;

  if (g_gems_caught_count < g_gems_count) {
    return;
  }

  for (int i = 0; pc->collider->_save_collisions && i < pc->collider->_n_collisions && i < pc->collider->_max_collisions; i++) {

    phRigid_Body2D* rb1 = pc->collisions[i].rigid_body1;
    phRigid_Body2D* rb2 = pc->collisions[i].rigid_body2;

    phRigid_Body2D* player_rb = NULL;

    if (rb1->_super->_entity->layer_mask & PLAYER_LAYER) {
      player_rb = rb1;
    } else if (rb2->_super->_entity->layer_mask & PLAYER_LAYER) {
      player_rb = rb2;
    }

    if (player_rb != NULL) {

      //TODO: move towards or similar
      player_rb->velocity = mSub_V2f(pc->rb->frame->position, player_rb->frame->position);
      // player_rb->frame->position = mAdd_V2f(
      //   player_rb->frame->position,
      //   mMul_f_V2f(0.02, mSub_V2f(pc->rb->frame->position, player_rb->frame->position))
      // );
      // player_rb->_super->is_active = true;

      pc->is_caught = true;

      if (!g_portal_catches_player) {
        g_portal_catch_time = geGet_Active_Game()->time;
      }
      g_portal_catches_player = true;

      break;

    }

  }

  g_portal_pos = pc->rb->frame->position;

}

void Destroy_Portal_Catcher_Sub_Component(geComponent* component) {

  Portal_Catcher* pc = component->_sub;

  free(pc);

}
