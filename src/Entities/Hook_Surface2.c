#include "Hook_Surface2.h"

#include "../Layers.h"

Hook_Surface2* Create_Hook_Surface2(mVector2f position, mVector2f scale) {

  geEntity* entity = geCreate_Entity();

  entity->layer_mask = HOOK_SURFACE_LAYER;

  mFrame2D* frame = new_mFrame2D(position, 0, scale);

  grSprite* sprite = grCreate_Sprite("../Resources/Textures/circle_orange_256.png",1,1);
  grRenderer* renderer = grCreate_Renderer_2D(frame, sprite->_model, sprite->_shader);

  phCircle_Collider2D* circle_c = new_phCircle_Collider2D(frame, 0.5);
  phRigid_Body2D* rb = new_phRigid_Body2D(frame, 1, 0.1, &circle_c->_super);
  rb->is_static = true;
  rb->is_static_rotation = true;
  rb->restitution = 0.25;

  Hook_Surface2* hs = malloc(sizeof(Hook_Surface2));
  *hs = (Hook_Surface2){

    ._super = entity,

    .frame = frame,

    .sprite = sprite,
    .renderer = renderer,

    .circle_c = circle_c,
    .rb = rb

  };

  geAdd_Component(frame->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(circle_c->_super._super, entity);
  geAdd_Component(rb->_super, entity);

  geSet_Sub_Entity(hs, Destroy_Hook_Surface2_Sub_Entity, entity);

  return hs;

}

void Destroy_Hook_Surface2_Sub_Entity(geEntity* entity) {

  Hook_Surface2* hs = entity->_sub;

  grDestroy_Sprite(hs->sprite);

  free(hs);

}
