#ifndef PH_COLLIDER_H
#define PH_COLLIDER_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/dATUM/dLList.h>
#include <Game_Engine/Maths/mFrame.h>

#include <Game_Engine/ECS/geComponent.h>

#define PH_N_COLLIDER       3
#define PH_AABB_COLLIDER    0
#define PH_CIRCLE_COLLIDER  1
#define PH_POLYGON_COLLIDER 2

typedef struct phCollider2D phCollider2D;

typedef struct phAABB_Collider2D phAABB_Collider2D;
typedef struct phCircle_Collider2D phCircle_Collider2D;
typedef struct phPolygon_Collider2D phPolygon_Collider2D;

D_HEADER_LLIST(phCollider2D*, phCollider2D_ptr);

typedef
struct phCollider2D {

  geComponent _super;

  dNode_LL(phCollider2D_ptr)* _cldr_node;

  mFrame2D* frame;

  bool _save_collisions;
  uint64_t _n_collisions;
  void* _collisions;
  uint64_t _max_collisions;

  void* _sub;
  int _collider_ID;

  void* attachment;

} phCollider2D;

struct phAABB_Collider2D {

  phCollider2D _super;

  float X_length;
  float Y_length;

};
struct phCircle_Collider2D {

  phCollider2D _super;

  float radius;

};

// ==========================
// Initialization/Termination
// ==========================

void phCollider2D_ctor(phCollider2D* self);

void phAABB_Collider2D_ctor(phAABB_Collider2D* self, mFrame2D* frame, float X_length, float Y_length);
void phCircle_Collider2D_ctor(phCircle_Collider2D* self, mFrame2D* frame,  float radius);

void phSet_Sub_Collider2D(void* sub, mFrame2D* frame, uint64_t collider_id, phCollider2D* collider);


#endif
