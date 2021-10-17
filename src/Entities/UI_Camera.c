#include "UI_Camera.h"

UI_Camera* Create_UI_Camera(geScene* scene) {

  UI_Camera* uic = malloc(sizeof(UI_Camera));
  if (uic == NULL) { return NULL; }

  uic->_super = geEntity_ctor(&uic->_super);
  geSet_Sub_Entity(uic, Destroy_UI_Camera_Sub_Entity, &uic->_super);

  uic->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  grCamera2D_ctor(&uic->camera, &uic->frame, 2,2);
  uic->camera.background_colour[1] = 1;
  uic->camera.background_colour[3] = 0;

  geAdd_Component(&uic->camera._super, &uic->_super);

  geAdd_Entity(&uic->_super, scene);

  return uic;

}

void Destroy_UI_Camera_Sub_Entity(geEntity* entity) {

  UI_Camera* uic = entity->_sub;

  free(uic);

}
