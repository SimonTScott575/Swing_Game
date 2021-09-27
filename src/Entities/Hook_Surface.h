#ifndef HOOK_SURFACE_H
#define HOOK_SURFACE_H

#include <Game_Engine/Game_Engine.h>

typedef struct Hook_Surface Hook_Surface;

struct Hook_Surface {

  geEntity* _super;

  mFrame2D* frame;

  grColour_Render* cr;
  grRenderer* renderer;

  phAABB_Collider2D* aabb_c;
  phRigid_Body2D* rb;

};

Hook_Surface* Create_Hook_Surface(mVector2f position, mVector2f scale);

void Destroy_Hook_Surface_Sub_Entity(geEntity* entity);

#endif
