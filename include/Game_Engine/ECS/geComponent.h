#ifndef GE_COMPONENT_H
#define GE_COMPONENT_H

#include <stdbool.h>

#include <Game_Engine/dATUM/dLList.h>

//!!! fwd header
typedef struct geEntity geEntity;

typedef struct geComponent geComponent;
typedef uint32_t geComponent_Layer_Mask;
typedef uint64_t geComponent_ID;

typedef void (*geUpdate_Component_fn)(geComponent*);
typedef void (*geDestroy_Sub_Component_fn)(geComponent*);

D_HEADER_dLList(geComponent*, geComponent_ptr);

struct geComponent {

  geEntity* _entity; //!!! NOT SET, needed ?
  dNode_LL(geComponent_ptr)* _component_node;

  bool is_active;
  char* name; //? uniquely identifies the component, eg player_rigid_body
  geComponent_Layer_Mask layer_mask;
  geComponent_ID ID; //? identifies type of component, eg rb, renderer etc.

  void* _sub;
  geUpdate_Component_fn _update;
  geDestroy_Sub_Component_fn _destroy;

};

// ==============
// Initialization
// ==============

geComponent geComponent_init();

geComponent* geCreate_Component();

void geDestroy_Component(geComponent* component);

void geSet_Sub_Component(void* sub, geUpdate_Component_fn update, geDestroy_Sub_Component_fn _destroy, geComponent* component);

// ===

void geUnload_Component(geComponent* component); //! needs remove, put in entity ?

void geUpdate_Component(geComponent* component);

// ===

// void geRegister_New_Component_ID(geComponent_ID* id);

#endif
