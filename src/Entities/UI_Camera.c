#include "UI_Camera.h"

UI_Camera* Create_UI_Camera() {

  geEntity* entity = geCreate_Entity();

  mFrame2D* ui_frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grCamera2D* ui_camera = grCreate_Camera2D(ui_frame, 2,2);
  ui_camera->background_colour[1] = 1;
  ui_camera->background_colour[3] = 0;

  geAdd_Component(ui_frame->_super, entity);
  geAdd_Component(ui_camera->_super, entity);

  UI_Camera* uic = malloc(sizeof(UI_Camera));
  *uic = (UI_Camera){

    ._super = entity,

    .frame = ui_frame,
    .camera = ui_camera

  };

  geSet_Sub_Entity(uic, Destroy_UI_Camera_Sub_Entity, entity);

  return uic;

}

void Destroy_UI_Camera_Sub_Entity(geEntity* entity) {

  UI_Camera* uic = entity->_sub;

  free(uic);

}
