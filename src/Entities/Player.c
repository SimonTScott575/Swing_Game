#include "Player.h"

#include "../Layers.h"

Player* Create_Player(geScene* scene) {

  Player* player = malloc(sizeof(Player));
  if (player == NULL) { return NULL; }

  player->_super = geEntity_ctor(&player->_super);
  geSet_Sub_Entity(player, Destroy_Player_Sub_Entity, &player->_super);
  player->_super.layer_mask = PLAYER_LAYER;

  player->frame = mFrame2D_init(mVector2f_ZERO, 0, mVector2f_ONE);

  player->sprite = grCreate_Sprite("../Resources/Textures/circle_red_256.png", 1, 1);
  grRenderer_2D_ctor(&player->renderer, &player->frame, player->sprite->_model, player->sprite->_shader);

  player->circle_c = new_phCircle_Collider2D(&player->frame, 0.5);
  phRigid_Body2D_ctor(&player->rb, &player->frame, 1, 0.5 * 0.5*0.5, &player->circle_c->_super);
  player->rb.restitution = 0.25;

  Player_Controller_ctor(&player->pc, &player->rb);

  geAdd_Component(&player->renderer._super, &player->_super);
  geAdd_Component(player->circle_c->_super._super, &player->_super);
  geAdd_Component(&player->rb._super, &player->_super);
  geAdd_Component(&player->pc._super, &player->_super);

  geAdd_Entity(&player->_super, scene);

  return player;

}

void Destroy_Player_Sub_Entity(geEntity* entity) {

  Player* player = entity->_sub;

  grDestroy_Sprite(player->sprite);

  free(player);

}
