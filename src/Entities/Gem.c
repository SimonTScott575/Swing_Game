#include "Gem.h"

#include "../Layers.h"

Gem* Create_Gem(mVector2f position, geScene* scene) {

  Gem* gem = malloc(sizeof(Gem));
  if (gem == NULL) { return NULL; }

  gem->_super = geEntity_ctor(&gem->_super);
  geSet_Sub_Entity(gem, Destroy_Gem_Sub_Entity, &gem->_super);
  gem->_super.layer_mask = GEM_LAYER;

  gem->frame = mFrame2D_init(position, 0, (mVector2f){{0.4,0.4}});

  gem->sprite = grCreate_Sprite("../Resources/Textures/circle_white_blur_512.png", 2, 2);
  grRenderer_2D_ctor(&gem->renderer, &gem->frame, gem->sprite->_model, gem->sprite->_shader);

  gem->circle_c = new_phCircle_Collider2D(&gem->frame, 0.5);
  phRigid_Body2D_ctor(&gem->rb, &gem->frame, 1, 0.1, &gem->circle_c->_super);
  gem->rb.is_static = gem->rb.is_static_rotation = true;
  gem->rb.is_transparent = true;

  Gem_Controller_ctor(&gem->gc, &gem->renderer, &gem->rb);

  geAdd_Component(&gem->renderer._super, &gem->_super);
  geAdd_Component(gem->circle_c->_super._super, &gem->_super);
  geAdd_Component(&gem->rb._super, &gem->_super);
  geAdd_Component(&gem->gc._super, &gem->_super);

  geAdd_Entity(&gem->_super, scene);

  return gem;

}

void Destroy_Gem_Sub_Entity(geEntity* entity) {

  Gem* gem = entity->_sub;

  grDestroy_Sprite(gem->sprite);

  free(gem);

}
