//TODO: del polygon, currently memory leak!

#include <Game_Engine/Physics/phCollider.h>

#include <stdlib.h>
#include <math.h>

#include <Game_Engine/Maths/mVector.h>

D_SOURCE_dLList(phCollider2D*, phCollider2D_ptr);

// ======
// static
// ======

// static void del_phCollider2D_void(void* arg) {
//   del_phCollider2D(arg);
// }

// ==============
// Initialization
// ==============

phCollider2D init_phCollider2D(mFrame2D* frame, uint64_t collider_id) {
  return (phCollider2D){
    ._super = NULL,

    ._cldr_node = NULL,
    .frame = frame,

    ._save_collisions = false,
    ._n_collisions = 0,
    ._collisions = NULL,
    ._max_collisions = 0,

    ._collider_ID = collider_id,
    ._sub = NULL,
    .attachment = NULL
  };
}

void phSet_Sub_Collider2D(void* sub, phCollider2D* collider) { //! preferably should have _destroy
  collider->_sub = sub;
}

phAABB_Collider2D* new_phAABB_Collider2D(mFrame2D* frame, float X_length, float Y_length) {

  phAABB_Collider2D* aabb = malloc(sizeof(phAABB_Collider2D));
  *aabb = (phAABB_Collider2D){
    .X_length = X_length,
    .Y_length = Y_length
  };

  aabb->_super = init_phCollider2D(frame, PH_AABB_COLLIDER);
  phSet_Sub_Collider2D(aabb, &aabb->_super);

  aabb->_super._super = geCreate_Component();
  geSet_Sub_Component(&aabb->_super, NULL, del_phCollider2D_Sub_Component, aabb->_super._super);

  return aabb;

}
phCircle_Collider2D* new_phCircle_Collider2D(mFrame2D* frame,  float radius) {

  phCircle_Collider2D* circle = malloc(sizeof(phCircle_Collider2D));
  *circle = (phCircle_Collider2D){
    .radius = radius
  };

  circle->_super = init_phCollider2D(frame, PH_CIRCLE_COLLIDER);
  phSet_Sub_Collider2D(circle, &circle->_super);

  circle->_super._super = geCreate_Component();
  geSet_Sub_Component(&circle->_super, NULL, del_phCollider2D_Sub_Component, circle->_super._super);

  return circle;

}
// phPolygon_Collider2D* new_phPolygon_Collider2D(mFrame2D* frame, float* vertices, uint64_t n) {
//
//   phPolygon_Collider2D* polygon = malloc(sizeof(phPolygon_Collider2D));
//   *polygon = (phPolygon_Collider2D){
//     .vertices_length = n, //? malloc vertices and copy?
//     .vertices = malloc( n * sizeof(mVector2f) ),
//     .normals = malloc( n * sizeof(mVector2f) )
//   };
//
//   // set vertices and normals
//   polygon->vertices[0] = (mVector2f){{ vertices[0], vertices[1] }};
//   for (int i = 0; i < n-1; i++) {
//
//     polygon->vertices[i + 1] = (mVector2f){{ vertices[2*i + 2], vertices[2*i + 1 + 2] }};
//
//     mVector2f delta_v = mSub_V2f(polygon->vertices[i+1], polygon->vertices[i]);
//     delta_v = mNormalized_V2f(delta_v);
//     polygon->normals[i] = (mVector2f){{ delta_v.i[1], -delta_v.i[0] }};
//
//   }
//   mVector2f delta_v = mSub_V2f(polygon->vertices[0], polygon->vertices[n-1]);
//   delta_v = mNormalized_V2f(delta_v);
//   polygon->normals[n-1] = (mVector2f){{ delta_v.i[1], -delta_v.i[0] }};
//
//   // set super
//   polygon->_super = (phCollider2D){
//     .frame = frame,
//     ._collider_ID = PH_POLYGON_COLLIDER,
//     ._sub = polygon,
//     .attachment = NULL
//   };
//
//   return polygon;
// }

// void del_phCollider2D(phCollider2D* collider) {
//
//   geDestroy_Component(collider->_super);
//   free(collider->_sub); //!!! geomtry vertices/normals not freed for polygon
//
// }
void del_phCollider2D_Sub_Component(geComponent* component) {

  phCollider2D* collider = component->_sub;

  free(collider->_sub); //!!! geomtry vertices/normals not freed for polygon

}
