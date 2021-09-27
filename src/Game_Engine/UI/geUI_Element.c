#include <Game_Engine/UI/geUI_Element.h>

D_SOURCE_dLList(geUI_Element*, geUI_Element_ptr);

geUI_Element init_geUI_Element(mFrame2D* frame) {

  return (geUI_Element){
    ._super = NULL,

    .x = 0, // relative position
    .y = 0, // relative position
    .frame = frame, // absolute offset

    ._sub = NULL,
    ._update = NULL,
    ._destroy = NULL
  };

}

void geSet_Sub_UI_Element(void* sub, geUpdate_UI_Element_fn update, geDestroy_UI_Element_fn destroy, geUI_Element* uie) {
  uie->_sub = sub;
  uie->_update = update;
  uie->_destroy = destroy;
}

void geDestroy_UI_Element_Sub_Component(geComponent* component) {

  geUI_Element* uie = component->_sub;

  if (uie->_destroy != NULL) {
    uie->_destroy(uie->_sub);
  }

}

void geUpdate_UI_Element(geUI_Element* uie, float x_length, float mouse_X, float mouse_Y, geWindow* window) {

  if (uie->_update != NULL) {
    uie->_update(uie, x_length, mouse_X, mouse_Y, window);
  }

}
