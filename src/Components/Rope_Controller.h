#ifndef ROPE_CONTROLLER_H
#define ROPE_CONTROLLER_H

#define GE_INCLUDE_GLFW
#include <Game_Engine/Game_Engine.h>

#define MAX_ROPE_CLIMB_SPEED 10
#define ROPE_CLIMP_ACCELERATION 0.4

typedef
struct Rope_Controller {

  geComponent _super;

  mFrame2D* frame;
  grRenderer* renderer;
  mFrame2D* hook_f;
  grRenderer* hook_r;

  grCamera2D* camera2D;

  bool is_hitting;
  bool init_rod_phase;
  bool init_spring_phase;
  bool rod_phase;
  bool spring_phase;
  bool climb_phase;

  phRod_Joint2D* rod_j;
  phSpring_Joint2D* spring_j;

  phRigid_Body2D* dest_rb;
  mVector2f dest_pos;

  phRB_System2D* rb_sys;

  float r_v;

} Rope_Controller;

void Rope_Controller_ctor(
  Rope_Controller* self,
  mFrame2D* frame, mFrame2D* hook_f,
  grRenderer* renderer, grRenderer* hook_r,
  phRod_Joint2D* rod_j, phSpring_Joint2D* spring_j
);
void Update_Rope_Controller(geComponent* component);
void Destroy_Rope_Controller_Sub_Component(geComponent* component);

#endif
