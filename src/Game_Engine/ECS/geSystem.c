#include <Game_Engine/ECS/geSystem.h>

#include <stdlib.h>

D_SOURCE_dLList(geSystem*, geSystem_ptr);

// ====================
// Creation/Destruction
// ====================

geSystem* geCreate_System(void* sub, geUpdate_fn update, geDestroy_fn destroy) {

  geSystem* system = malloc(sizeof(geSystem));

  *system = (geSystem){

    ._system_node = NULL,

    .is_active = true,

    ._sub = sub,
    ._update = update,
    ._destroy = destroy

  };

  return system;

}

void geDestroy_System(geSystem* system) {

  free(system);

}

// ===

void geUpdate_System(geSystem* system) {

  if (system->_update != NULL) {
    system->_update(system->_sub);
  }

}
