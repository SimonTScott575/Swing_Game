#include "Hook_Surface.h"

#include "../Layers.h"

Hook_Surface* Create_Hook_Surface(mVector2f position, mVector2f scale, geScene* scene) {

  Hook_Surface* hs = malloc(sizeof(Hook_Surface));
  if (hs == NULL) { return NULL; }

  geEntity_ctor(&hs->_super);
  geSet_Sub_Entity(hs, Destroy_Hook_Surface_Sub_Entity, &hs->_super);
  hs->_super.layer_mask = HOOK_SURFACE_LAYER;

  hs->frame = mFrame2D_init(position, 0, scale);

  hs->cr = grColour_Render_init(
    (float[4]){226/256.0, 113/256.0, 29/256.0, 1},
    grRect2D_Mesh
  );
  grRenderer_2D_ctor(&hs->renderer, &hs->frame, &hs->cr._model, &hs->cr._shader);

  phAABB_Collider2D_ctor(&hs->aabb_c, &hs->frame, 1,1);
  phRigid_Body2D_ctor(&hs->rb, &hs->frame, 1, 0.1, &hs->aabb_c._super);
  hs->rb.is_static = true;
  hs->rb.is_static_rotation = true;
  hs->rb.restitution = 0.25;

  geAdd_Component(&hs->renderer._super, &hs->_super);
  geAdd_Component(&hs->aabb_c._super._super, &hs->_super);
  geAdd_Component(&hs->rb._super, &hs->_super);

  geAdd_Entity(&hs->_super, scene);

  return hs;

}

void Destroy_Hook_Surface_Sub_Entity(geEntity* entity) {

  Hook_Surface* hs = entity->_sub;

  grColour_Render_term(&hs->cr);

  free(hs);

}
