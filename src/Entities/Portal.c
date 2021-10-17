#include "Portal.h"

Portal* Create_Portal(mVector2f position, float radius, geScene* scene) {

  Portal* portal = malloc(sizeof(Portal));
  if (portal == NULL) { return NULL; }

  portal->_super = geEntity_ctor(&portal->_super);
  geSet_Sub_Entity(portal, Destroy_Portal_Sub_Entity, &portal->_super);

  portal->frame = mFrame2D_init(position, 0, (mVector2f){{2*radius,2*radius}});

  Portal_Renderer_ctor(&portal->pr);
  grRenderer_2D_ctor(&portal->renderer, &portal->frame, portal->pr.model, portal->pr.shader);

  portal->collider = new_phCircle_Collider2D(&portal->frame, 0.5);
  phRigid_Body2D_ctor(&portal->rb, &portal->frame, 1, 0.1, &portal->collider->_super);
  portal->rb.is_static = true;
  portal->rb.is_static_rotation = true; //?
  portal->rb.is_transparent = true;

  Portal_Catcher_ctor(&portal->pc, radius, &portal->rb);

  geAdd_Component(&portal->pr._super, &portal->_super);
  geAdd_Component(&portal->renderer._super, &portal->_super);
  geAdd_Component(portal->collider->_super._super, &portal->_super);
  geAdd_Component(&portal->rb._super, &portal->_super);
  geAdd_Component(&portal->pc._super, &portal->_super);

  geAdd_Entity(&portal->_super, scene);

  return portal;

}

void Destroy_Portal_Sub_Entity(geEntity* entity) {

  Portal* portal = entity->_sub;

  free(portal);

}
