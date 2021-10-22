#include "Rope.h"

Rope* Create_Rope(phRigid_Body2D* source_rb, geScene* scene) {

  Rope* rope = malloc(sizeof(Rope));
  if (rope == NULL) { return NULL; }

  geEntity_ctor(&rope->_super);
  geSet_Sub_Entity(rope, Destroy_Rope_Sub_Entity, &rope->_super);

  rope->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);
  rope->hook_f = mFrame2D_init(mVector2f_ZERO, 0, (mVector2f){{0.15,0.15}});

  rope->sprite = grCreate_Sprite("../Resources/Textures/square_red_256.png",1 ,1);
  grRenderer_2D_ctor(&rope->renderer, &rope->frame, &rope->sprite->_model, &rope->sprite->_shader);

  rope->hook_sprite = grCreate_Sprite("../Resources/Textures/circle_red_256.png",1,1);
  grRenderer_2D_ctor(&rope->hook_r, &rope->hook_f, &rope->hook_sprite->_model, &rope->hook_sprite->_shader);
  rope->hook_r._super.is_active = false;

  phRod_Joint2D_ctor(&rope->rod_j, 1, rope->frame.position, source_rb, mVector2f_ZERO, NULL);
  rope->rod_j._super._super.is_active = false;
  phSpring_Joint2D_ctor(&rope->spring_j, 50, 5, rope->frame.position, source_rb, mVector2f_ZERO, NULL);
  rope->spring_j._super._super.is_active = false;

  Rope_Controller_ctor(&rope->rc, &rope->frame, &rope->hook_f, &rope->renderer, &rope->hook_r, &rope->rod_j, &rope->spring_j);

  geAdd_Component(&rope->renderer._super, &rope->_super);
  geAdd_Component(&rope->hook_r._super, &rope->_super);
  geAdd_Component(&rope->rod_j._super._super, &rope->_super);
  geAdd_Component(&rope->spring_j._super._super, &rope->_super);
  geAdd_Component(&rope->rc._super, &rope->_super);

  geAdd_Entity(&rope->_super, scene);

  return rope;

}

void Destroy_Rope_Sub_Entity(geEntity* entity) {

  Rope* rope = entity->_sub;

  grDestroy_Sprite(rope->sprite);
  grDestroy_Sprite(rope->hook_sprite);

  free(rope);

}
