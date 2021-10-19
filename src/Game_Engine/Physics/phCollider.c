//TODO: del polygon, currently memory leak!

#include <Game_Engine/Physics/phCollider.h>

#include <stdlib.h>
#include <math.h>

#include <Game_Engine/Maths/mVector.h>

D_SOURCE_LLIST(phCollider2D*, phCollider2D_ptr);

// ==========================
// Initialization/Termination
// ==========================

void phCollider2D_ctor(phCollider2D* self) {
  *self = (phCollider2D){
    ._cldr_node = NULL,
    .frame = NULL,

    ._save_collisions = false,
    ._n_collisions = 0,
    ._collisions = NULL,
    ._max_collisions = 0,

    ._sub = NULL,
    .attachment = NULL
  };
  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, NULL, NULL, &self->_super);
}

void phAABB_Collider2D_ctor(phAABB_Collider2D* self, mFrame2D* frame, float X_length, float Y_length) {

  *self = (phAABB_Collider2D){
    .X_length = X_length,
    .Y_length = Y_length
  };

  phCollider2D_ctor(&self->_super);
  phSet_Sub_Collider2D(self, frame, PH_AABB_COLLIDER, &self->_super);

}
void phCircle_Collider2D_ctor(phCircle_Collider2D* self, mFrame2D* frame,  float radius) {

  *self = (phCircle_Collider2D){
    .radius = radius
  };

  phCollider2D_ctor(&self->_super);
  phSet_Sub_Collider2D(self, frame, PH_CIRCLE_COLLIDER, &self->_super);

}

void phSet_Sub_Collider2D(void* sub, mFrame2D* frame, uint64_t collider_id, phCollider2D* collider) { //! preferably should have _destroy
  collider->_sub = sub;
  collider->frame = frame;
  collider->_collider_ID = collider_id;
}
