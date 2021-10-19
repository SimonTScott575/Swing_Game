#include <Game_Engine/ECS/geSystem.h>

#include <stdlib.h>

#include <Game_Engine/ge_common.h>

D_SOURCE_LLIST(geSystem*, geSystem_ptr);

// ====================
// Creation/Destruction
// ====================

geSystem* geCreate_System(void* sub, geUpdate_fn update, geDestroy_fn destroy) {

  geSystem* system = malloc(sizeof(geSystem));
  if (system == NULL) {
    GE_DEBUG_LOG("%s\n",
                 "Game_Engine DEBUG : ECS/geSystem\n"
                 "                    system malloc fail\n");
    return NULL;
  }

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
