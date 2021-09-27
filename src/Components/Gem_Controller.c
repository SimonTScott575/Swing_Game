#include "Gem_Controller.h"

#include <stdlib.h>

#include "../Layers.h"

int gems_count = 0;
int gems_caught_count = 0;

Gem_Controller* Create_Gem_Controller(grRenderer* renderer, phRigid_Body2D* rb) {

  Gem_Controller* gc = malloc(sizeof(Gem_Controller));

  *gc = (Gem_Controller){
    ._super = geCreate_Component(),

    .renderer = renderer,
    .rb = rb
  };

  phSave_Collider_Collisions(gc->rb->collider, gc->collisions, 10);

  geSet_Sub_Component(gc, Update_Gem_Controller, Destroy_Gem_Controller_Sub_Component, gc->_super);

  return gc;

}

void Update_Gem_Controller(geComponent* component) {

  Gem_Controller* gc = component->_sub;

  if (gc->rb->collider->_n_collisions > 0) {
    phRigid_Body2D* rb1 = gc->collisions[0].rigid_body1;
    phRigid_Body2D* rb2 = gc->collisions[0].rigid_body2;
    if ( (rb1->_super->_entity->layer_mask & PLAYER_LAYER) || (rb2->_super->_entity->layer_mask & PLAYER_LAYER) ) {
      gc->rb->_super->is_active = false;
      gc->renderer->_super->is_active = false;
    }

    gems_caught_count += 1;
  }

}

void Destroy_Gem_Controller_Sub_Component(geComponent* component) {

  Gem_Controller* gc = component->_sub;

  free(gc);

}
