#ifndef PORTAL_CATCHER_H
#define PORTAL_CATCHER_H

#include <Game_Engine/Game_Engine.h>

#include <stdbool.h>

typedef
struct Portal_Catcher {

  geComponent _super;

  float radius;
  bool is_caught;

  phCollider2D* collider;
  phRigid_Body2D* rb;
  phCollision2D collisions[10];

} Portal_Catcher;

extern mVector2f g_portal_pos;
extern int g_portal_catches_player;
extern float g_portal_catch_time;

void Portal_Catcher_ctor(Portal_Catcher* self, float radius, phRigid_Body2D* rb);

void Update_Portal_Catcher(geComponent* component);

#endif
