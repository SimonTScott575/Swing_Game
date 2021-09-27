#ifndef GEM_H
#define GEM_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Gem_Controller.h"

typedef struct Gem Gem;

struct Gem {

  geEntity* _super;

  mFrame2D* frame;

  grSprite* sprite;
  grRenderer* renderer;

  phCircle_Collider2D*  circle_c;
  phRigid_Body2D* rb;

  Gem_Controller* gc;

};

Gem* Create_Gem(mVector2f position);

void Destroy_Gem_Sub_Entity(geEntity* entity);

#endif
