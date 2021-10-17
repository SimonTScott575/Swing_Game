#ifndef GEM_CONTROLLER_H
#define GEM_CONTROLLER_H

#include <stdbool.h>

#include <Game_Engine/Game_Engine.h>

typedef
struct Gem_Controller {

  geComponent _super;

  grRenderer* renderer;

  phRigid_Body2D* rb;
  phCollision2D collisions[10];

  bool is_caught;
  int index;

} Gem_Controller;

extern int g_gems_count;
extern int g_gems_caught_count;
extern int* g_gems_is_caught;
extern mVector2f* g_gem_positions;

void Gem_Controller_ctor(Gem_Controller* self, grRenderer* renderer, phRigid_Body2D* rb);

void Update_Gem_Controller(geComponent* component);

void Set_Global_Gem_Data(Gem_Controller** gem_controllers, int new_gems_count, int new_gems_caught_count);


#endif
