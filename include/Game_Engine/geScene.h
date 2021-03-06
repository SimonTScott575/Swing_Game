#ifndef GE_SCENE_H
#define GE_SCENE_H

#include <Game_Engine/ECS/geEntity.h>
#include <Game_Engine/ECS/geSystem.h>

typedef struct geScene geScene;

typedef void (*geLoad_Scene_fn)(geScene*);

D_HEADER_LLIST(geScene*, geScene_ptr);

typedef
struct geScene {

  dNode_LL(geScene_ptr)* _scene_node;

  dLList(geSystem_ptr)* _systems;
  dLList(geEntity_ptr)* _entities;
  bool _is_loaded;

  geLoad_Scene_fn _load;

} geScene;

// ====================
// Creation/Destruction
// ====================

geScene* geCreate_Scene(geLoad_Scene_fn load);

void geDestroy_Scene(geScene* scene);

// ===

// Calls the geLoad_Scene_fn
void geLoad_Scene(geScene* scene);

// Calls the unload entity/system functions of added entities/systems
void geUnload_Scene(geScene* scene);

// Updates entities then systems in order added
void geUpdate_Scene(geScene* scene);

// ========================
// Entity/System Management
// ========================

dNode_LL(geEntity_ptr)* geAdd_Entity(geEntity* entity, geScene* scene);
dNode_LL(geEntity_ptr)* geAdd_Entity_Before(geEntity* new_entity, geEntity* entity2, geScene* scene);
dNode_LL(geEntity_ptr)* geAdd_Entity_After(geEntity* new_entity, geEntity* entity2, geScene* scene);

void geRemove_Entity(geEntity* entity, geScene* scene);

geEntity* geGet_First_Entity(geScene* scene);
geEntity* geGet_Next_Entity(geEntity* entity);

dNode_LL(geSystem_ptr)* geAdd_System(geSystem* system, geScene* scene);
dNode_LL(geSystem_ptr)* geAdd_System_Before(geSystem* new_system, geSystem* system2, geScene* scene);
dNode_LL(geSystem_ptr)* geAdd_System_After(geSystem* new_system, geSystem* system2, geScene* scene);

void geRemove_System(geSystem* system, geScene* scene);

geSystem* geGet_First_System(geScene* scene);
geSystem* geGet_Next_System(geSystem* system);

#endif
