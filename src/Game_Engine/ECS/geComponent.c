#include <Game_Engine/ECS/geComponent.h>

D_SOURCE_dLList(geComponent*, geComponent_ptr);

// ======
// static
// ======

// static geComponent_ID geHighest_Component_ID = 0;

// ====================
// Creation/Destruction
// ====================

geComponent geComponent_init() { //? id ?

  return (geComponent){
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

geComponent* geCreate_Component() { //? id ?

  geComponent* component = malloc(sizeof(geComponent));

  *component = (geComponent){
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

  return component;

}

void geDestroy_Component(geComponent* component) { //!!! MUST remove from entity components list (see unload) ? //! NEED component list !

  if (component->_destroy != NULL) {
    component->_destroy(component);
  }

  free(component);

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
// ===

// void geRegister_New_Component_ID(geComponent* component, geComponent_ID* id) {
//   geHighest_Component_ID += 1;
//
//   *id = geHighest_Component_ID;
//
//   //...
// }
