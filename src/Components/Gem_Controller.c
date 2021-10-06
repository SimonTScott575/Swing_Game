#include "Gem_Controller.h"

#include <stdlib.h>

#include "../Layers.h"

int g_gems_count = 0;
int g_gems_caught_count = 0;
int* g_gems_is_caught = NULL;
mVector2f* g_gem_positions = NULL;

Gem_Controller* Create_Gem_Controller(grRenderer* renderer, phRigid_Body2D* rb) {

  Gem_Controller* gc = malloc(sizeof(Gem_Controller));

  *gc = (Gem_Controller){
    ._super = geCreate_Component(),

    .renderer = renderer,

    .rb = rb,

    .is_caught = false,
    .index = -1
  };

  geSet_Sub_Component(gc, Update_Gem_Controller, Destroy_Gem_Controller_Sub_Component, gc->_super);

  phSave_Collider_Collisions(gc->rb->collider, gc->collisions, 10);

  return gc;

}

void Update_Gem_Controller(geComponent* component) {

  Gem_Controller* gc = component->_sub;

  if (!gc->is_caught && gc->rb->collider->_n_collisions > 0) {
    phRigid_Body2D* rb1 = gc->collisions[0].rigid_body1;
    phRigid_Body2D* rb2 = gc->collisions[0].rigid_body2;
    if ( (rb1->_super->_entity->layer_mask & PLAYER_LAYER) || (rb2->_super->_entity->layer_mask & PLAYER_LAYER) ) {

      gc->rb->_super->is_active = false;
      gc->renderer->_super->is_active = false;

      gc->is_caught = true;

      g_gems_caught_count += 1;
      g_gems_is_caught[gc->index] = true;

    }

  }

}

void Destroy_Gem_Controller_Sub_Component(geComponent* component) {

  Gem_Controller* gc = component->_sub;

  free(gc);

}

void Set_Global_Gem_Data(Gem_Controller** gem_controllers, int new_gems_count, int new_gems_caught_count) {

  if (new_gems_count == 0) {

    if (g_gems_is_caught != NULL) {
      free(g_gems_is_caught);
      g_gems_is_caught = NULL;
    }
    if (g_gem_positions != NULL) {
      free(g_gem_positions);
      g_gem_positions = NULL;
    }

  } else {

    if (g_gems_is_caught == NULL) {
      g_gems_is_caught = malloc(new_gems_count * sizeof *g_gems_is_caught);
      g_gem_positions = malloc(new_gems_count * sizeof *g_gem_positions);
    } else {
      g_gems_is_caught = realloc(g_gems_is_caught, new_gems_count * sizeof *g_gems_is_caught);
      g_gem_positions = realloc(g_gem_positions, new_gems_count * sizeof *g_gem_positions);
    }

    for (int i = 0; i < new_gems_count; i++) {

      g_gems_is_caught[i] = false;
      g_gem_positions[i] = gem_controllers[i]->rb->frame->position;

      gem_controllers[i]->index = i;

    }

  }

  g_gems_count = new_gems_count;
  g_gems_caught_count = new_gems_caught_count;

}
