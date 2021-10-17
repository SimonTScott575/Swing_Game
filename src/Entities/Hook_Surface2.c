#include "Hook_Surface2.h"

#include "../Layers.h"

Hook_Surface2* Create_Hook_Surface2(mVector2f position, mVector2f scale, geScene* scene) {

  Hook_Surface2* hs = malloc(sizeof(Hook_Surface2));
  if (hs == NULL) { return NULL; }

  hs->_super = geEntity_ctor(&hs->_super);
  geSet_Sub_Entity(hs, Destroy_Hook_Surface2_Sub_Entity, &hs->_super);
  hs->_super.layer_mask = HOOK_SURFACE_LAYER;

  hs->frame = mFrame2D_init(position, 0, scale);

  hs->sprite = grCreate_Sprite("../Resources/Textures/circle_orange_256.png",1,1);
  grRenderer_2D_ctor(&hs->renderer, &hs->frame, hs->sprite->_model, hs->sprite->_shader);

  hs->circle_c = new_phCircle_Collider2D(&hs->frame, 0.5);
  phRigid_Body2D_ctor(&hs->rb, &hs->frame, 1, 0.1, &hs->circle_c->_super);
  hs->rb.is_static = true;
  hs->rb.is_static_rotation = true;
  hs->rb.restitution = 0.25;

  geAdd_Component(&hs->renderer._super, &hs->_super);
  geAdd_Component(hs->circle_c->_super._super, &hs->_super);
  geAdd_Component(&hs->rb._super, &hs->_super);

  geAdd_Entity(&hs->_super, scene);

  return hs;

}

void Destroy_Hook_Surface2_Sub_Entity(geEntity* entity) {

  Hook_Surface2* hs = entity->_sub;

  grDestroy_Sprite(hs->sprite);

  free(hs);

}
