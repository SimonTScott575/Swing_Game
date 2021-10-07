#ifndef PORTAL_CATCHER_H
#define PORTAL_CATCHER_H

#include <Game_Engine/Game_Engine.h>

#include <stdbool.h>

typedef
struct Portal_Catcher {

  geComponent* _super;

  float radius;
  bool is_caught;

  phCollider2D* collider;
  phRigid_Body2D* rb;
  phCollision2D collisions[10];

} Portal_Catcher;

extern mVector2f g_portal_pos;

Portal_Catcher* Create_Portal_Catcher(float radius, phRigid_Body2D* rb);

void Update_Portal_Catcher(geComponent* component);

void Destroy_Portal_Catcher_Sub_Component(geComponent* component);

#endif
