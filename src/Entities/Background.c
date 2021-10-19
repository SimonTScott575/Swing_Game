#include "Background.h"

Background* Create_Background(float x_length, float y_length, geScene* scene) {

  Background* bg = malloc(sizeof(Background));
  if (bg == NULL) { return NULL; }

  geEntity_ctor(&bg->_super);
  geSet_Sub_Entity(bg, Destroy_Background_Sub_Entity, &bg->_super);

  bg->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  bg->sprite = grCreate_Sprite("../Resources/Textures/gradient_orange_256.png", x_length,y_length);
  if (bg->sprite == NULL) {
    free(bg);
    return NULL;
  }

  grRenderer_2D_ctor(&bg->renderer, &bg->frame, &bg->sprite->_model, &bg->sprite->_shader);

  geAdd_Component(&bg->renderer._super, &bg->_super);

  geAdd_Entity(&bg->_super, scene);

  return bg;

}

void Destroy_Background_Sub_Entity(geEntity* entity) {

  Background* bg = entity->_sub;

  grDestroy_Sprite(bg->sprite);

  free(bg);

}
