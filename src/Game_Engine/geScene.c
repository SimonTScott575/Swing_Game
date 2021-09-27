#include <Game_Engine/geScene.h>

#include <stdio.h>
#include <stdlib.h>

D_SOURCE_dLList(geScene*, geScene_ptr);

// ====================
// Creation/Destruction
// ====================

geScene* geCreate_Scene(geLoad_Scene_fn load) {

  geScene* scene = malloc(sizeof(geScene));

  scene->_scene_node = NULL;

  scene->_entities = new_dLList(geEntity_ptr)(0, NULL);
  scene->_systems = new_dLList(geSystem_ptr)(0,NULL);
  scene->_is_loaded = false;

  scene->_load = load;

  return scene;

}

void geDestroy_Scene(geScene* scene) {

  del_dLList(geEntity_ptr)(scene->_entities);
  del_dLList(geSystem_ptr)(scene->_systems);

  free(scene);

}

// ===

void geLoad_Scene(geScene* scene) {

  if (scene->_load != NULL) {
    scene->_load(scene);
  }

  scene->_is_loaded = true;

}

void geUnload_Scene(geScene* scene) {

  dNode_LL(geEntity_ptr)* entity_node = scene->_entities->start;
  dNode_LL(geEntity_ptr)* next_entity_node;
  for ( ; entity_node != NULL; entity_node = next_entity_node) {

    geUnload_Entity(entity_node->element);

    next_entity_node = entity_node->next;
    dRemove_LL(geEntity_ptr)(entity_node, scene->_entities); //? TEMP or not ?

  }

  dNode_LL(geSystem_ptr)* system_node = scene->_systems->start;
  dNode_LL(geSystem_ptr)* next_system_node;
  for ( ; system_node != NULL; system_node = next_system_node) {

    geDestroy_System(system_node->element);

    next_system_node = system_node->next;
    dRemove_LL(geSystem_ptr)(system_node, scene->_systems);

  }

  scene->_is_loaded = false;

}

void geUpdate_Scene(geScene* scene) {

  dNode_LL(geEntity_ptr)* entity_node = scene->_entities->start;
  while (entity_node != NULL) {

    if (entity_node->element->is_active) {
      geUpdate_Entity(entity_node->element);
    }

    entity_node = entity_node->next;

  }

  dNode_LL(geSystem_ptr)* system_node = scene->_systems->start;
  while (system_node != NULL) {

    if (system_node->element->is_active) {
      geUpdate_System(system_node->element);
    }

    system_node = system_node->next;

  }

}

// ===

void geAdd_Entity(geEntity* entity, geScene* scene) {
  entity->_entity_node = dAppend_LL(geEntity_ptr)(entity, scene->_entities);
}
void geAdd_Entity_Before(geEntity* new_entity, geEntity* entity2, geScene* scene) {
  new_entity->_entity_node = dInsert_Before_LL(geEntity_ptr)(new_entity, entity2->_entity_node, scene->_entities);
}
void geAdd_Entity_After(geEntity* new_entity, geEntity* entity2, geScene* scene) {
  new_entity->_entity_node = dInsert_After_LL(geEntity_ptr)(new_entity, entity2->_entity_node, scene->_entities);
}

void geRemove_Entity(geEntity* entity, geScene* scene) {
  dRemove_LL(geEntity_ptr)(entity->_entity_node, scene->_entities);
  entity->_entity_node = NULL;
}

geEntity* geGet_First_Entity(geScene* scene) {

  if (scene->_entities == NULL || scene->_entities->start == NULL) {
    return NULL;
  }

  return scene->_entities->start->element;

}
geEntity* geGet_Next_Entity(geEntity* entity) {

  if (entity->_entity_node == NULL || entity->_entity_node->next == NULL) {
    return NULL;
  }

  return entity->_entity_node->next->element;

}
//TODO: get last/prev

void geAdd_System(geSystem* system, geScene* scene) {
  system->_system_node = dAppend_LL(geSystem_ptr)(system, scene->_systems);
}
void geAdd_System_Before(geSystem* new_system, geSystem* system2, geScene* scene) {
  new_system->_system_node = dInsert_Before_LL(geSystem_ptr)(new_system, system2->_system_node, scene->_systems);
}
void geAdd_System_After(geSystem* new_system, geSystem* system2, geScene* scene) {
  new_system->_system_node = dInsert_After_LL(geSystem_ptr)(new_system, system2->_system_node, scene->_systems);
}

void geRemove_System(geSystem* system, geScene* scene) {
  dRemove_LL(geSystem_ptr)(system->_system_node, scene->_systems);
  system->_system_node = NULL;
}

geSystem* geGet_First_System(geScene* scene) {

  if (scene->_systems == NULL || scene->_systems->start == NULL) {
    return NULL;
  }

  return scene->_systems->start->element;

}
geSystem* geGet_Next_System(geSystem* system) {

  if (system->_system_node == NULL || system->_system_node->next == NULL) {
    return NULL;
  }

  return system->_system_node->next->element;

}
//TODO: get last/prev





// void geAdd_Entity(geEntity* entity, geScene* scene) {
//   entity->_entity_node = dAppend_LLEntity(entity, scene->_entities);
// }
//
// void geRemove_Entity(geEntity* entity, geScene* scene) {
//   dRemove_LLEntity(entity->_entity_node, scene->_entities);
// }
