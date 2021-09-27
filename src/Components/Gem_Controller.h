#ifndef GEM_CONTROLLER_H
#define GEM_CONTROLLER_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Gem_Controller {

  geComponent* _super;

  grRenderer* renderer;

  phRigid_Body2D* rb;

  phCollision2D collisions[10];

} Gem_Controller;

extern int gems_count;
extern int gems_caught_count;

Gem_Controller* Create_Gem_Controller(grRenderer* renderer, phRigid_Body2D* rb);

void Update_Gem_Controller(geComponent* component);

void Destroy_Gem_Controller_Sub_Component(geComponent* component);


#endif
