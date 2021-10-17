#ifndef ROPE_H
#define ROPE_H

#include <Game_Engine/Game_Engine.h>

#include "../Components/Rope_Controller.h"

typedef
struct Rope {

  geEntity _super;

  mFrame2D frame;

  grSprite* sprite;
  grRenderer renderer;

  phRod_Joint2D rod_j;
  phSpring_Joint2D spring_j;
  Rope_Controller rc;

} Rope;

Rope* Create_Rope(phRigid_Body2D* source_rb, geScene* scene);

void Destroy_Rope_Sub_Entity(geEntity* entity);

#endif
