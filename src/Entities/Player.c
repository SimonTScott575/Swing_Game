#include "Player.h"

#include "../Layers.h"

Player* Create_Player() {

  geEntity* entity = geCreate_Entity();

  entity->layer_mask = PLAYER_LAYER;

  mFrame2D* frame = new_mFrame2D(mVector2f_ZERO, 0, mVector2f_ONE);

  grSprite* sprite = grCreate_Sprite("../Resources/Textures/circle_red_256.png", 1, 1);
  grRenderer* renderer = grCreate_Renderer_2D(frame, sprite->_model, sprite->_shader);

  phCircle_Collider2D* circle_c = new_phCircle_Collider2D(frame, 0.5);
  phRigid_Body2D* rb = new_phRigid_Body2D(frame, 1, 0.1, &circle_c->_super);
  rb->restitution = 0.25;

  Player_Controller* pc = Create_Player_Controller(rb);

  geAdd_Component(frame->_super, entity);
  geAdd_Component(sprite->_super, entity);
  geAdd_Component(renderer->_super, entity);
  geAdd_Component(circle_c->_super._super, entity);
  geAdd_Component(rb->_super, entity);
  geAdd_Component(pc->_super, entity);

  Player* player = malloc(sizeof(Player));
  *player = (Player){
    ._super = entity,

    .frame = frame,

    .renderer = renderer,
    .sprite = sprite,

    .circle_c = circle_c,
    .rb = rb,

    .pc = pc
  };

  geSet_Sub_Entity(player, Destroy_Player_Sub_Entity, entity);

  return player;

}

void Destroy_Player_Sub_Entity(geEntity* entity) {

  Player* player = entity->_sub;

  free(player);

}
