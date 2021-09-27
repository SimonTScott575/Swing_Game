#include "Portal.h"

Portal* Create_Portal(mVector2f position, float radius) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(position, 0, (mVector2f){{2*radius,2*radius}});

  Portal_Renderer* pr = Create_Portal_Renderer();
  grRenderer* renderer = grCreate_Renderer_2D(frame, pr->model, pr->shader);

  phCircle_Collider2D* collider = new_phCircle_Collider2D(frame, 0.5);
  phRigid_Body2D* rb = new_phRigid_Body2D(frame, 1, 0.1, &collider->_super);
  rb->is_static = true;
  rb->is_static_rotation = true; //?
  rb->is_transparent = true;

  Portal_Catcher* pc = Create_Portal_Catcher(radius, rb);

  geAdd_Component(frame->_super, entity);
  geAdd_Component(pr->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(collider->_super._super, entity);
  geAdd_Component(rb->_super, entity);
  geAdd_Component(pc->_super, entity);

  Portal* portal = malloc(sizeof(Portal));
  *portal = (Portal){

    ._super = entity,

    .frame = frame,

    .pr = pr,
    .renderer = renderer,

    .collider = collider,
    .rb = rb,

    .pc = pc

  };

  geSet_Sub_Entity(portal, Destroy_Portal_Sub_Entity, entity);

  return portal;

}

void Destroy_Portal_Sub_Entity(geEntity* entity) {

  Portal* portal = entity->_sub;

  free(portal);

}
