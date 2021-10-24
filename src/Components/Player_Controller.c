#include "Player_Controller.h"

void Player_Controller_ctor(Player_Controller* self, phRigid_Body2D* rb) {

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Player_Controller, NULL, &self->_super);

  self->rb = rb;
  self->rb->_super.is_active = false;

  self->last_pos = rb->frame->position.i[0];

}

void Update_Player_Controller(geComponent* component) {

  Player_Controller* pc = component->_sub;

  pc->last_pos = pc->rb->frame->position.i[0];

  bool D_down = geKey_Down(geGet_Active_Game(), GE_KB_D);
  bool A_down = geKey_Down(geGet_Active_Game(), GE_KB_A);
  if (D_down || A_down) {
    float new_vel = pc->rb->velocity.i[0] + ( D_down - A_down )*0.2;
    if (-7 < pc->rb->velocity.i[0] && new_vel > 0 || pc->rb->velocity.i[0] < 7 && new_vel < 0) {
      pc->rb->velocity.i[0] = new_vel;
    }
  }

}
