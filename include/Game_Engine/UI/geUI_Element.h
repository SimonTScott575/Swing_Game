#ifndef GE_UI_ELEMENT
#define GE_UI_ELEMENT

#include <Game_Engine/Maths/mFrame.h>
#include <Game_Engine/dATUM/dLList.h>
#include <Game_Engine/ECS/geComponent.h>
#include <Game_Engine/Graphics/grRenderer.h>
#include <Game_Engine/geWindow.h>

typedef struct geUI_Element geUI_Element;

typedef void (*geUpdate_UI_Element_fn)(geUI_Element* uie, float x_length, float mouse_X, float mouse_Y, geWindow* window);
typedef void (*geDestroy_UI_Element_fn)(geUI_Element* uie);

D_HEADER_LLIST(geUI_Element*, geUI_Element_ptr);

typedef
struct geUI_Element {

  geComponent _super;

  float x; // relative position
  float y; // relative position
  mFrame2D* frame; // absolute offset (units of height/2)

  void* _sub;
  geUpdate_UI_Element_fn _update;
  geDestroy_UI_Element_fn _destroy;

} geUI_Element;

// ==========================
// Initialization/Termination
// ==========================

void geUI_Element_ctor(geUI_Element* self, mFrame2D* frame);
void geUI_Element_Sub_Component_dtor(geComponent* component);

void geSet_Sub_UI_Element(void* sub, geUpdate_UI_Element_fn update, geDestroy_UI_Element_fn destroy, geUI_Element* uie);

// ===

void geUpdate_UI_Element(geUI_Element* uie, float x_length, float mouse_X, float mouse_Y, geWindow* window);

#endif
