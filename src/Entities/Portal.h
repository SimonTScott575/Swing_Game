#ifndef PORTAL_H
#define PORTAL_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Portal_Catcher.h"
#include "../Components/Portal_Renderer.h"

typedef struct Portal Portal;

struct Portal {

  geEntity* _super;

  mFrame2D* frame;

  Portal_Renderer* pr;
  grRenderer* renderer;

  phCircle_Collider2D* collider;
  phRigid_Body2D* rb;

  Portal_Catcher* pc;

};

//NOTE: radius changes scale, not model dimensions
Portal* Create_Portal(mVector2f position, float radius);

void Destroy_Portal_Sub_Entity(geEntity* entity);

#endif
