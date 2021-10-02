#include "Rope.h"

Rope* Create_Rope(phRigid_Body2D* source_rb) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grSprite* sprite = grCreate_Sprite("../Resources/Textures/square_red_256.png",1 ,1);
  grRenderer* renderer = grCreate_Renderer_2D(frame, sprite->_model, sprite->_shader);

  phRod_Joint2D* rod_j = new_phRod_Joint2D(1, frame->position, source_rb, mVector2f_ZERO, NULL);
  rod_j->_super._super->is_active = false;
  phSpring_Joint2D* spring_j = new_phSpring_Joint2D(50, 5, frame->position, source_rb, mVector2f_ZERO, NULL);
  spring_j->_super._super->is_active = false;

  Rope_Controller* rc = Create_Rope_Controller(frame, renderer, rod_j, spring_j);

  Rope* rope = malloc(sizeof(Rope));
  *rope = (Rope){

    ._super = entity,

    .frame = frame,

    .sprite = sprite,
    .renderer = renderer,

    .rod_j = rod_j,
    .spring_j = spring_j,
    .rc = rc

  };

  geAdd_Component(frame->_super, entity);
  geAdd_Component(sprite->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(rod_j->_super._super, entity);
  geAdd_Component(spring_j->_super._super, entity);
  geAdd_Component(rc->_super, entity);

  geSet_Sub_Entity(rope, Destroy_Rope_Sub_Entity, entity);

  return rope;

}

void Destroy_Rope_Sub_Entity(geEntity* entity) {

  Rope* rope = entity->_sub;

  free(rope);

}
