#ifndef GE_UI_MANAGER_H
#define GE_UI_MANAGER_H

#include <Game_Engine/ECS/geSystem.h>
#include <Game_Engine/geWindow.h>
#include <Game_Engine/Graphics/grCamera.h>

#include <Game_Engine/UI/geUI_Element.h>
#include <Game_Engine/UI/geButton_UI.h>

typedef struct geUI_Manager geUI_Manager;

struct geUI_Manager {

  geSystem* _super;

  grCamera2D* camera;
  dLList(geUI_Element_ptr)* _elements;

};

geUI_Manager* geCreate_UI_Manager(grCamera2D* camera);

void geDestroy_UI_Manager(void* arg);

void geUpdate_UI_Manager(void* arg);

#endif
