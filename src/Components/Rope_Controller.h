#ifndef ROPE_CONTROLLER_H
#define ROPE_CONTROLLER_H

#define GE_INCLUDE_GLFW
#include <Game_Engine/Game_Engine.h>

typedef struct Rope_Controller Rope_Controller;

struct Rope_Controller {

  geComponent* _super;

  mFrame2D* frame;
  grRenderer* renderer;

  grCamera2D* camera2D;

  bool is_hitting;
  bool rod_phase;
  bool spring_phase;
  mVector2f dest_pos;

  phRod_Joint2D* rod_j;
  phSpring_Joint2D* spring_j;

  phRigid_Body2D* dest_rb;

  phRB_System2D* rb_sys;

  mVector2f last_pos;

};

Rope_Controller* Create_Rope_Controller(mFrame2D* frame, grRenderer* renderer, phRod_Joint2D* rod_j, phSpring_Joint2D* spring_j);
void Update_Rope_Controller(geComponent* component);
void Destroy_Rope_Controller_Sub_Component(geComponent* component);

#endif
