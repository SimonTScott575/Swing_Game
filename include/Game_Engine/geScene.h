#ifndef GE_SCENE_H
#define GE_SCENE_H

#include <Game_Engine/ECS/geEntity.h>
#include <Game_Engine/ECS/geSystem.h>

typedef struct geScene geScene;

typedef void (*geLoad_Scene_fn)(geScene*);

D_HEADER_dLList(geScene*, geScene_ptr);

struct geScene {

  dNode_LL(geScene_ptr)* _scene_node;

  dLList(geSystem_ptr)* _systems;
  dLList(geEntity_ptr)* _entities;
  bool _is_loaded;

  geLoad_Scene_fn _load;

};

// ====================
// Creation/Destruction
// ====================

geScene* geCreate_Scene();

void geDestroy_Scene(geScene* scene);

// ===

void geLoad_Scene(geScene* scene);

void geUnload_Scene(geScene* scene); //? remove ? //? put in game ? //? static ?

void geUpdate_Scene(geScene* scene);

//? end_scene like end_game ?

// ===

void geAdd_Entity(geEntity* entity, geScene* scene);
void geAdd_Entity_Before(geEntity* new_entity, geEntity* entity2, geScene* scene);
void geAdd_Entity_After(geEntity* new_entity, geEntity* entity2, geScene* scene);

void geRemove_Entity(geEntity* entity, geScene* scene);

geEntity* geGet_First_Entity(geScene* scene);
geEntity* geGet_Next_Entity(geEntity* entity);

// void geAdd_Entity(geEntity* entity, geScene* scene);
//
// void geRemove_Entity(geEntity* entity, geScene* scene);

void geAdd_System(geSystem* system, geScene* scene);
void geAdd_System_Before(geSystem* new_system, geSystem* system2, geScene* scene);
void geAdd_System_After(geSystem* new_system, geSystem* system2, geScene* scene);

void geRemove_System(geSystem* system, geScene* scene);

geSystem* geGet_First_System(geScene* scene);
geSystem* geGet_Next_System(geSystem* system);

#endif
