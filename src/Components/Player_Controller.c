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
    3*( glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_D) - glfwGetKey(geGet_Active_Window()->_window_ID, GLFW_KEY_A) ),
    150*( geKey_Down_Stroke(geGet_Active_Game(), GLFW_KEY_SPACE) ) //TEMP
  }};

  printf("%f\n",pc->rb->frame->position.i[0] - pc->last_pos);
  // printf("%f\n", pc->rb->velocity.i[0]);
  pc->last_pos = pc->rb->frame->position.i[0];

}

void Destroy_Player_Controller_Sub_Component(geComponent* component) {

  Player_Controller* pc = component->_sub;

  free(pc);

}
