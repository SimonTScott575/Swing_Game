#include "Background.h"

Background* Create_Background(float x_length, float y_length) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grSprite* sprite = grCreate_Sprite("../Resources/Textures/gradient_orange_256.png", x_length,y_length);
  grRenderer* renderer = grCreate_Renderer_2D(frame, sprite->_model, sprite->_shader);

  geAdd_Component(frame->_super, entity);
  geAdd_Component(renderer->_super, entity);

  Background* bg = malloc(sizeof(Background));
  *bg = (Background){

    ._super = entity,

    .frame = frame,
    .sprite = sprite,
    .renderer = renderer

  };

  geSet_Sub_Entity(bg, Destroy_Background_Sub_Entity, entity);

  return bg;

}

void Destroy_Background_Sub_Entity(geEntity* entity) {

  Background* bg = entity->_sub;

  grDestroy_Sprite(bg->sprite);

  free(bg);

}
