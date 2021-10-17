#include "Rope.h"

Rope* Create_Rope(phRigid_Body2D* source_rb, geScene* scene) {

  Rope* rope = malloc(sizeof(Rope));
  if (rope == NULL) { return NULL; }

  rope->_super = geEntity_ctor(&rope->_super);
  geSet_Sub_Entity(rope, Destroy_Rope_Sub_Entity, &rope->_super);

  rope->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  rope->sprite = grCreate_Sprite("../Resources/Textures/square_red_256.png",1 ,1);
  grRenderer_2D_ctor(&rope->renderer, &rope->frame, rope->sprite->_model, rope->sprite->_shader);

  phRod_Joint2D_ctor(&rope->rod_j, 1, rope->frame.position, source_rb, mVector2f_ZERO, NULL);
  rope->rod_j._super._super.is_active = false;
  phSpring_Joint2D_ctor(&rope->spring_j, 50, 5, rope->frame.position, source_rb, mVector2f_ZERO, NULL);
  rope->spring_j._super._super.is_active = false;

  Rope_Controller_ctor(&rope->rc, &rope->frame, &rope->renderer, &rope->rod_j, &rope->spring_j);

  geAdd_Component(&rope->renderer._super, &rope->_super);
  geAdd_Component(&rope->rod_j._super._super, &rope->_super);
  geAdd_Component(&rope->spring_j._super._super, &rope->_super);
  geAdd_Component(&rope->rc._super, &rope->_super);

  geAdd_Entity(&rope->_super, scene);

  return rope;

}

void Destroy_Rope_Sub_Entity(geEntity* entity) {

  Rope* rope = entity->_sub;

  grDestroy_Sprite(rope->sprite);

  free(rope);

}
