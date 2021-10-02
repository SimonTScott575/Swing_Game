#include "Player_Controller.h"

Player_Controller* Create_Player_Controller(phRigid_Body2D* rb) {

  Player_Controller* pc = malloc(sizeof(Player_Controller));

  pc->_super = geCreate_Component();
  geSet_Sub_Component(pc, Update_Player_Controller, Destroy_Player_Controller_Sub_Component, pc->_super);

  pc->rb = rb;
  pc->rb->_super->is_active = false;

  pc->last_pos = rb->frame->position.i[0];

  return pc;

}

void Update_Player_Controller(geComponent* component) {

  Player_Controller* pc = component->_sub;

  pc->rb->force = (mVector2f){{
    0, // 10*( glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_D) - glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_A) ),
    150*( geKey_Down_Stroke(geGet_Active_Game(), GLFW_KEY_SPACE) ) //TEMP
  }};

  pc->last_pos = pc->rb->frame->position.i[0];

  bool D_down = glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_D);
  bool A_down = glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_A);
  if (D_down || A_down) {
    float new_vel = pc->rb->velocity.i[0] + ( D_down - A_down )*0.2;
    if (-7 < pc->rb->velocity.i[0] && new_vel > 0 || pc->rb->velocity.i[0] < 7 && new_vel < 0) {
      pc->rb->velocity.i[0] = new_vel;
    }
  }

}

void Destroy_Player_Controller_Sub_Component(geComponent* component) {

  Player_Controller* pc = component->_sub;

  free(pc);

}
