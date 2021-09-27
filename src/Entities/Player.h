#ifndef PLAYER_H
#define PLAYER_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Player_Controller.h"

typedef struct Player Player;

struct Player {

  geEntity* _super;

  mFrame2D* frame;

  grSprite* sprite;
  grRenderer* renderer;

  phCircle_Collider2D* circle_c;
  phRigid_Body2D* rb;

  Player_Controller* pc;

};

Player* Create_Player();

void Destroy_Player_Sub_Entity(geEntity* entity);

#endif
