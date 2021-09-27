#include "Gem.h"

#include "../Layers.h"

Gem* Create_Gem(mVector2f position) {

  geEntity* entity = geCreate_Entity();

  entity->layer_mask = GEM_LAYER;

  mFrame2D* frame = new_mFrame2D(position, 0, (mVector2f){{0.4,0.4}});

  grSprite* sprite = grCreate_Sprite("../Resources/Textures/circle_white_256.png", 1, 1);
  grRenderer* renderer = grCreate_Renderer_2D(frame, sprite->_model, sprite->_shader);

  phAABB_Collider2D* aabb_c = new_phAABB_Collider2D(frame, 1, 1);
  phRigid_Body2D* rb = new_phRigid_Body2D(frame, 1, 0.1, &aabb_c->_super);
  rb->is_static = rb->is_static_rotation = true;
  rb->is_transparent = true;

  Gem_Controller* gc = Create_Gem_Controller(renderer, rb);

  Gem* gem = malloc(sizeof(Gem));
  *gem = (Gem){
    ._super = entity,
    .frame = frame,
    .sprite = sprite,
    .renderer = renderer,
    .aabb_c = aabb_c,
    .rb = rb,
    .gc = gc
  };

  geAdd_Component(frame->_super, entity);
  geAdd_Component(sprite->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(aabb_c->_super._super, entity);
  geAdd_Component(rb->_super, entity);
  geAdd_Component(gc->_super, entity);

  geSet_Sub_Entity(gem, Destroy_Gem_Sub_Entity, entity);

  return gem;

}

void Destroy_Gem_Sub_Entity(geEntity* entity) {

  Gem* gem = entity->_sub;

  free(gem);

}
