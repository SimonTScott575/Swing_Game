#ifndef HOOK_SURFACE2_H
#define HOOK_SURFACE2_H

#include <Game_Engine/Game_Engine.h>

typedef struct Hook_Surface2 Hook_Surface2;

struct Hook_Surface2 {

  geEntity _super;

  mFrame2D frame;

  grSprite* sprite;
  grRenderer renderer;

  phCircle_Collider2D* circle_c;
  phRigid_Body2D rb;

};

Hook_Surface2* Create_Hook_Surface2(mVector2f position, mVector2f scale, geScene* scene);

void Destroy_Hook_Surface2_Sub_Entity(geEntity* entity);

#endif
