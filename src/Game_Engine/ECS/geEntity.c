#include <Game_Engine/ECS/geEntity.h>

#include <stdio.h>

D_SOURCE_LLIST(geEntity*, geEntity_ptr);

// ==========================
// Initialization/Termination
// ==========================

void geEntity_ctor(geEntity* self) {

  *self = (geEntity){
    ._entity_node = NULL,

    .is_active = true,
    .name = NULL,
    .layer_mask = 0,
    .ID = 0,

    ._components = new_dLList(geComponent_ptr)(0,NULL),

    ._sub = NULL,
    ._destroy = NULL
  };

}
void geEntity_dtor(geEntity* entity) {

  del_dLList(geComponent_ptr)(entity->_components);

  if (entity->_destroy != NULL) {
    entity->_destroy(entity);
  }

}

void geSet_Sub_Entity(void* sub, geDestroy_Entity_fn destroy, geEntity* entity) {

  entity->_sub = sub;
  entity->_destroy = destroy;

}

// ===

bool geComponent_Is_Active(geComponent* component) {
  if (component->_entity != NULL) {
    return component->is_active && component->_entity->is_active;
  }
  return component->is_active;
}

void geUnload_Entity(geEntity* entity) {

  dNode_LL(geComponent_ptr)* component_node = entity->_components->start;
  dNode_LL(geComponent_ptr)* next_component_node;
  for ( ; component_node != NULL; component_node = next_component_node) {

    geComponent_dtor(component_node->element);

    next_component_node = component_node->next;
    dRemove_LL(geComponent_ptr)(component_node, entity->_components);

  }

  geEntity_dtor(entity);

}

void geUpdate_Entity(geEntity* entity) {

  dNode_LL(geComponent_ptr)* component_node = entity->_components->start;
  while (component_node != NULL) {

    if (component_node->element->is_active) {
      geUpdate_Component(component_node->element);
    }

    component_node = component_node->next;

  }

}

// ===

void geAdd_Component(geComponent* component, geEntity* entity) {
  component->_component_node = dAppend_LL(geComponent_ptr)(component, entity->_components);
  component->_entity = entity;
}
void geAdd_Component_Before(geComponent* new_component, geComponent* component2, geEntity* entity) {
  new_component->_component_node = dInsert_Before_LL(geComponent_ptr)(new_component, component2->_component_node, entity->_components);
  new_component->_entity = entity;
}
void geAdd_Component_After(geComponent* new_component, geComponent* component2, geEntity* entity) {
  new_component->_component_node = dInsert_After_LL(geComponent_ptr)(new_component, component2->_component_node, entity->_components);
  new_component->_entity = entity;
}

void geRemove_Component(geComponent* component, geEntity* entity) {
  dRemove_LL(geComponent_ptr)(component->_component_node, entity->_components);
  component->_component_node = NULL;
  component->_entity = NULL;
}

geComponent* geGet_First_Component(geEntity* entity) {

  if (entity->_components == NULL || entity->_components->start == NULL) {
    return NULL;
  }

  return entity->_components->start->element;

}
geComponent* geGet_Next_Component(geComponent* component) {

  if (component->_component_node == NULL || component->_component_node->next == NULL) {
    return NULL;
  }

  return component->_component_node->next->element;

}
