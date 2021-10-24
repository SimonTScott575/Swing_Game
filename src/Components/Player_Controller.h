#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <Game_Engine/Game_Engine.h>

typedef struct Player_Controller Player_Controller;

struct Player_Controller {

  geComponent _super;

  phRigid_Body2D* rb;

  float last_pos;

};

void Player_Controller_ctor(Player_Controller* self, phRigid_Body2D* rb);

void Update_Player_Controller(geComponent* component);

void Destroy_Player_Controller_Sub_Component(geComponent* component);

#endif
