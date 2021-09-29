#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#define GE_INCLUDE_GLFW
#include <Game_Engine/Game_Engine.h>

typedef struct Player_Controller Player_Controller;

struct Player_Controller {

  geComponent* _super;

  phRigid_Body2D* rb;

  float last_pos;

};

Player_Controller* Create_Player_Controller();

void Update_Player_Controller(geComponent* component);

void Destroy_Player_Controller_Sub_Component(geComponent* component);

#endif
