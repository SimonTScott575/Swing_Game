#ifndef GE_ENTITY_H
#define GE_ENTITY_H

#include <stdbool.h>

#include "geComponent.h"

typedef struct geEntity geEntity;

typedef void (*geDestroy_Entity_fn)(geEntity* entity);

D_HEADER_LLIST(geEntity*, geEntity_ptr);

typedef uint32_t geEntity_Layer_Mask;
typedef uint64_t geEntity_ID;

typedef
struct geEntity {

  dNode_LL(geEntity_ptr)* _entity_node;

  bool is_active;
  char* name;
  geEntity_Layer_Mask layer_mask;
  geEntity_ID ID;

  dLList(geComponent_ptr)* _components;

  void* _sub;
  geDestroy_Entity_fn _destroy;

} geEntity;

// ==========================
// Initialization/Termination
// ==========================

void geEntity_ctor(geEntity* self);
void geEntity_dtor(geEntity* entity);

void geSet_Sub_Entity(void* sub, geDestroy_Entity_fn destroy, geEntity* entity);

// ===

bool geComponent_Is_Active(geComponent* component);

void geUnload_Entity(geEntity* entity); //! needs remove ! //? put in scene ?

void geUpdate_Entity(geEntity* entity);

// ===

void geAdd_Component(geComponent* component, geEntity* entity);
void geAdd_Component_Before(geComponent* new_component, geComponent* component2, geEntity* entity);
void geAdd_Component_After(geComponent* new_component, geComponent* component2, geEntity* entity);

void geRemove_Component(geComponent* component, geEntity* entity);

geComponent* geGet_First_Component(geEntity* entity);
geComponent* geGet_Next_Component(geComponent* component);

#endif
