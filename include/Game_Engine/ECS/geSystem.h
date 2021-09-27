#ifndef GE_SYSTEM_H
#define GE_SYSTEM_H

#include <Game_Engine/dATUM/dLList.h>

#include "geComponent.h"

typedef struct geSystem geSystem;

typedef void (*geUpdate_fn)(void*);
typedef void (*geDestroy_fn)(void*);

D_HEADER_dLList(geSystem*, geSystem_ptr);

struct geSystem {

  dNode_LL(geSystem_ptr)* _system_node;

  bool is_active;

  void* _sub;
  geUpdate_fn _update;
  geDestroy_fn _destroy;

};

// ====================
// Creation/Destruction
// ====================

geSystem* geCreate_System(void* sub, geUpdate_fn update, geDestroy_fn destroy);

void geDestroy_System(geSystem* system);

// ===

void geUpdate_System(geSystem* system);

#endif
