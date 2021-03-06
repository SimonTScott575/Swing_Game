#include <Game_Engine/ECS/geComponent.h>

D_SOURCE_LLIST(geComponent*, geComponent_ptr);

// ====================
// Creation/Destruction
// ====================

void geComponent_ctor(geComponent* self) {

  *self = (geComponent){
    ._entity = NULL,
    ._component_node = NULL,

    .is_active = true,
    .name = NULL,
    .layer_mask = 0,
    .ID = 0,

    ._sub = NULL,
    ._update = NULL,
    ._destroy = NULL
  };

}
void geComponent_dtor(geComponent* component) {
  if (component->_destroy != NULL) {
    component->_destroy(component);
  }
}

void geSet_Sub_Component(void* sub, geUpdate_Component_fn update, geDestroy_Sub_Component_fn destroy, geComponent* component) {

  component->_sub = sub;
  component->_update = update;
  component->_destroy = destroy;

}

// ===

void geUpdate_Component(geComponent* component) {

  if (component->_update != NULL) {
    component->_update(component);
  }

}
