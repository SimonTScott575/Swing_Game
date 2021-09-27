#include "Hook_Surface.h"

#include "../Layers.h"

Hook_Surface* Create_Hook_Surface(mVector2f position, mVector2f scale) {

  geEntity* entity = geCreate_Entity();

  entity->layer_mask = HOOK_SURFACE_LAYER;

  mFrame2D* frame = new_mFrame2D(position, 0, scale);

  grColour_Render* cr = grCreate_Colour_Render(
    (float[4]){226/256.0, 113/256.0, 29/256.0, 1},
    grRect2D_Mesh
  );
  grRenderer* renderer = grCreate_Renderer_2D(frame, cr->_model, cr->_shader);

  phAABB_Collider2D* aabb_c = new_phAABB_Collider2D(frame, 1,1);
  phRigid_Body2D* rb = new_phRigid_Body2D(frame, 1, 0.1, &aabb_c->_super);
  rb->is_static = true;
  rb->is_static_rotation = true;
  rb->restitution = 0.25;

  Hook_Surface* hs = malloc(sizeof(Hook_Surface));
  *hs = (Hook_Surface){

    ._super = entity,

    .frame = frame,

    .cr = cr,
    .renderer = renderer,

    .aabb_c = aabb_c,
    .rb = rb

  };

  geAdd_Component(frame->_super, entity);
  geAdd_Component(cr->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(aabb_c->_super._super, entity);
  geAdd_Component(rb->_super, entity);

  geSet_Sub_Entity(hs, Destroy_Hook_Surface_Sub_Entity, entity);

  return hs;

}

void Destroy_Hook_Surface_Sub_Entity(geEntity* entity) {

  Hook_Surface* hs = entity->_sub;

  free(hs);

}
