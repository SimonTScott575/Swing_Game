#include <Game_Engine/UI/geUI_Renderer.h>

// ======
// static
// ======

static void geDestroy_UI_Sub_Renderer(grRenderer* renderer);

// ==========================
// Initialization/Termination
// ==========================

geUI_Renderer* grCreate_UI_Renderer(geUI_Element* uie, grModel* model, grShader* shader) {

  geUI_Renderer* ui_r = malloc(sizeof(geUI_Renderer));

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO,0,mVector2f_ONE);

  grRenderer* renderer = grCreate_Renderer_2D(frame, model, shader);
  grSet_Sub_Renderer(ui_r, geDestroy_UI_Sub_Renderer, renderer);
  renderer->render_fn = geRender_UI_Renderer;

  *ui_r = (geUI_Renderer){

    ._super = renderer,

    .uie = uie,

    .frame = frame

  };

  return ui_r;

}

void geDestroy_UI_Sub_Renderer(grRenderer* renderer) {

  geUI_Renderer* ui_r = renderer->_sub;

  del_mFrame2D_Sub_Component(ui_r->frame->_super);

  free(ui_r);

};

// ===

void geRender_UI_Renderer(grRenderer* renderer, grCamera2D* camera) {

  geUI_Renderer* ui_r = renderer->_sub;
  geUI_Element* uie = ui_r->uie;

  mFrame2D* renderer_frame = ui_r->_super->frame;

  float ar = grGet_Active_Screen()->_Y_pixels/(float)grGet_Active_Screen()->_X_pixels;
  float Y_length = ar*camera->_X_length/2;

  renderer_frame->position = mAdd_V2f(
    (mVector2f){{uie->x*camera->_X_length/2,uie->y*Y_length}},
    uie->frame->position
  );
  renderer_frame->rotation = uie->frame->rotation;
  renderer_frame->scale = uie->frame->scale;

  mGenerate_transform_2D(renderer_frame);

  grRender_2D(renderer, camera);

}
