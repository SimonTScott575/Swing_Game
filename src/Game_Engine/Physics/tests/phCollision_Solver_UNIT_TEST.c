#include "../phCollision_Solver.h"
//!!! NEED rigid_bodies

#include <stdio.h>
#include <stdbool.h>

#include <Game_Engine/Maths/mVector.h>

int main() {

  mFrame2D frame1 = mFrame2D_I;
  mFrame2D frame2 = mFrame2D_I;

  phCollision2D collisions[100];

  // ====
  // AABB
  // ====

  frame1 = mFrame2D_I;
  frame2 = mFrame2D_I;
  frame2.scale.i[0] = 2;
  phAABB_Collider2D* c_AABB1 = new_phAABB_Collider2D(&frame1, 2,2);
  phAABB_Collider2D* c_AABB2 = new_phAABB_Collider2D(&frame2, 0.5,1);
  phRigid_Body2D rb_AABB1 = init_phRigid_Body2D(&frame1, 0, 0, &c_AABB1->_super);
  phRigid_Body2D rb_AABB2 = init_phRigid_Body2D(&frame2, 0, 0, &c_AABB2->_super);

  printf("AABB Testing\n");

  uint64_t n_collisions = phDetect_Collisions(&rb_AABB1, &rb_AABB2, collisions);
  printf("%d Boolean Test 1\n", n_collisions > 0 != true);
  for (int i= 0; i < n_collisions; i++) {
    printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
  }

  frame2.position.i[0] += 1.49;
  frame2.position.i[1] += 1.49;
  n_collisions = phDetect_Collisions(&rb_AABB1, &rb_AABB2, collisions);
  printf("%d Boolean Test 2\n", n_collisions > 0 != true);
  for (int i= 0; i < n_collisions; i++) {
    printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
  }

  frame2.position.i[0] += 0.02;
  frame2.position.i[1] += 0.02;
  n_collisions = phDetect_Collisions(&rb_AABB1, &rb_AABB2, collisions);
  printf("%d Boolean Test 3\n", n_collisions > 0 != false);
  for (int i= 0; i < n_collisions; i++) {
    printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
  }

  // --------
  // Ray Cast
  // --------

  frame2.position.i[0] = frame2.position.i[1] = 0;
  bool is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, mVector2f_X, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 1\n", is_ray_detection != false);

  frame2.position.i[1] += 1.1;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, mVector2f_X, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 2\n", is_ray_detection != false);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.position.i[1] = 0;
  frame2.position.i[0] = -0.51;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, mVector2f_X, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 3\n", is_ray_detection != false);

  frame2.position.i[0] += 5;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, mVector2f_X, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 4\n", is_ray_detection != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.position.i[1] = 0;
  frame2.position.i[0] = -5;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, (mVector2f){{-1,0}}, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 5\n", is_ray_detection != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.position = mVector2f_ZERO;
  frame2.position.i[0] = frame2.position.i[1] = -3;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, (mVector2f){{-1,-1.1}}, rb_AABB2.collider, collisions);
  printf("%d Ray Cast Boolean Test 6\n", is_ray_detection != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  // --------
  // Clean up
  // --------

  del_phCollider2D(&c_AABB1->_super);
  del_phCollider2D(&c_AABB2->_super);

  // ======
  // Circle
  // ======

  frame1 = mFrame2D_I;
  frame2 = mFrame2D_I;
  phCircle_Collider2D* c_circle1 = new_phCircle_Collider2D(&frame1, 1);
  phCircle_Collider2D* c_circle2 = new_phCircle_Collider2D(&frame2, 1);
  phRigid_Body2D rb1 = init_phRigid_Body2D(&frame1, 1, 1, &c_circle1->_super);
  phRigid_Body2D rb2 = init_phRigid_Body2D(&frame2, 1, 1, &c_circle2->_super);

  printf("Circle Testing\n");

  frame1.position.i[0] += 0.02;
  frame2.position.i[0] -= 0.02;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 1\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame1.position.i[0] = 2.01;
  frame2.position.i[0] = 0;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 2\n", n_collisions > 0 != false);

  frame1.position.i[0] = 1.99;
  frame2.position.i[0] = 0;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 3\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame1.position = (mVector2f){{9,11}};
  frame2.position = (mVector2f){{11,9}};
  float diff = 2*1.41 - 2;
  frame2.position.i[0] += -diff/sqrt(2);
  frame2.position.i[1] +=  diff/sqrt(2);
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 4\n", n_collisions > 0 != false);

  frame2.position.i[0] += -0.01/sqrt(2);
  frame2.position.i[1] +=  0.01/sqrt(2);
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 5\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  // --------
  // Ray Cast
  // --------

  frame2 = mFrame2D_I;

  frame2.position.i[0] = frame2.position.i[1] = 0;
  is_ray_detection = phRay_Cast_Circle(mVector2f_ZERO, mVector2f_X, &c_circle2->_super, collisions);
  printf("%d Ray Cast Boolean Test 1\n", is_ray_detection != false);

  frame2.position.i[1] += 1.1;
  is_ray_detection = phRay_Cast_AABB(mVector2f_ZERO, mVector2f_X, &c_circle2->_super, collisions);
  printf("%d Ray Cast Boolean Test 2\n", is_ray_detection != false);

  frame2.position.i[1] = 0;
  frame2.position.i[0] = 1.01;
  is_ray_detection = phRay_Cast_Circle(mVector2f_ZERO, mVector2f_X, &c_circle2->_super, collisions);
  printf("%d Ray Cast Boolean Test 3\n", is_ray_detection != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.position.i[1] = 0;
  frame2.position.i[0] = 0.99;
  is_ray_detection = phRay_Cast_Circle(mVector2f_ZERO, mVector2f_X, &c_circle2->_super, collisions);
  printf("%d Ray Cast Boolean Test 4\n", is_ray_detection != false);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.position.i[1] = -2;
  frame2.position.i[0] = -2;
  is_ray_detection = phRay_Cast_Circle(mVector2f_ZERO, (mVector2f){{-1,-1}}, &c_circle2->_super, collisions);
  printf("%d Ray Cast Boolean Test 5\n", is_ray_detection != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  // --------
  // Clean up
  // --------

  del_phCollider2D(&c_circle1->_super);
  del_phCollider2D(&c_circle2->_super);

  // ===========
  // AABB Circle
  // ===========

  frame1 = mFrame2D_I;
  frame2 = mFrame2D_I;
  c_AABB1 = new_phAABB_Collider2D(&frame1, 1, 1);
  c_circle2 = new_phCircle_Collider2D(&frame2, 1);
  rb1 = init_phRigid_Body2D(&frame1, 1, 1, &c_AABB1->_super);
  rb2 = init_phRigid_Body2D(&frame2, 1, 1, &c_circle2->_super);

  printf("AABB Circle Testing\n");

  frame1.position.i[0] += 0.02;
  frame2.position.i[0] -= 0.02;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 1\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame1.position = mVector2f_ZERO;
  frame2.position.i[0] = 1.51;
  frame2.position.i[1] = 0;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 2\n", n_collisions > 0 != false);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame1.position = mVector2f_ZERO;
  frame2.position.i[0] = 1.49;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 3\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame1.position = (mVector2f){{9,11}};
  frame2.position = (mVector2f){{11,9}};
  diff = 2*1.41 - (1.41/2 + 1);
  frame2.position.i[0] += -diff/sqrt(2);
  frame2.position.i[1] +=  diff/sqrt(2);
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 4\n", n_collisions > 0 != false);

  frame2.position.i[0] += -0.01/sqrt(2);
  frame2.position.i[1] +=  0.01/sqrt(2);
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 5\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.scale = (mVector2f){{0.5,0.5}};
  frame2.position.i[0] += -0.34;
  frame2.position.i[1] +=  0.34;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 6\n", n_collisions > 0 != false);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  frame2.scale = (mVector2f){{0.5,0.5}};
  frame2.position.i[0] += -0.02;
  frame2.position.i[1] +=  0.02;
  n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
  printf("%d Boolean Test 7\n", n_collisions > 0 != true);
  printf("\tdistance %f\n\tposition %f %f\n\tnormal %f %f\n",
    collisions[0].distance,
    collisions[0].position.i[0], collisions[0].position.i[1],
    collisions[0].normal.i[0], collisions[0].normal.i[1]
  );

  // --------
  // Clean up
  // --------

  del_phCollider2D(&c_AABB1->_super);
  del_phCollider2D(&c_circle2->_super);

  // ===========
  // Termination
  // ===========

  //!!! polygon vertices free!?

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// // -------
// // Polygon
// // -------
//
// float p_vertices[] = {
//   -0.5,-0.5,
//   0.5,-0.5,
//   1,0,
//   0.5,0.5,
//   -0.5,0.5
// };
//
// phCollider2D* c_polygon_1 = new_phCollider2D_POLYGON(&frame1, NULL, NULL, p_vertices, 5);
// phCollider2D* c_polygon_2 = new_phCollider2D_POLYGON(&frame2, NULL, NULL, p_vertices, 5);
// phRigid_Body2D rb_polygon_1 = init_phRigid_Body2D(&frame1, 0, 0, c_polygon_1);
// phRigid_Body2D rb_polygon_2 = init_phRigid_Body2D(&frame2, 0, 0, c_polygon_2);
//
// printf("Polygon Testing\n");
//
// frame1 = mFrame2D_I;
// frame2 = mFrame2D_I;
// mGenerate_transform_2D(&frame1);
// mGenerate_transform_2D(&frame2);
// n_collisions = phDetect_Collisions(&rb_polygon_1, &rb_polygon_2, collisions);
// printf("%d Boolean test 1\n", n_collisions > 0 != true);
// for (int i= 0; i < n_collisions; i++) {
//   printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
// }
//
// frame1.position = mMul_f_V2f(0.5, mVector2f_X);
// mGenerate_transform_2D(&frame1);
// n_collisions = phDetect_Collisions(&rb_polygon_1, &rb_polygon_2, collisions);
// printf("%d Boolean test 2\n", n_collisions > 0 != true);
// for (int i= 0; i < n_collisions; i++) {
//   printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
// }
//
// frame1 = mFrame2D_I;
// frame2 = mFrame2D_I;
// frame2.position = mVector2f_ZERO;
// frame2.position = mAdd_V2f( mMul_f_V2f(6, mVector2f_Y), mMul_f_V2f(4, mVector2f_X) );
// frame2.rotation = -3.14f/4;
// frame1.position = mVector2f_ZERO;
// frame1.position = mAdd_V2f( mMul_f_V2f(4, mVector2f_Y), mMul_f_V2f(6, mVector2f_X) );
// frame1.rotation = 3.14f*3.0f/4.0f;
// mGenerate_transform_2D(&frame1);
// mGenerate_transform_2D(&frame2);
// n_collisions = phDetect_Collisions(&rb_polygon_1, &rb_polygon_2, collisions);
// printf("%d Boolean test 3\n", n_collisions > 0 != false);
// for (int i= 0; i < n_collisions; i++) {
//   printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
// }
//
// mVector2f direction = {{1,-1}};
// direction = mNormalized_V2f(direction);
// frame2.position = mAdd_V2f( frame2.position, mMul_f_V2f(0.41, direction) );
// frame1.position = mAdd_V2f( frame1.position, mMul_f_V2f(-0.41, direction) );
// mGenerate_transform_2D(&frame1);
// mGenerate_transform_2D(&frame2);
// n_collisions = phDetect_Collisions(&rb_polygon_1, &rb_polygon_2, collisions);
// printf("%d Boolean test 4\n", n_collisions > 0 != false);
// for (int i= 0; i < n_collisions; i++) {
//   printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
// }
//
// frame2.position = mAdd_V2f( frame2.position, mMul_f_V2f(0.01, direction) );
// frame1.position = mAdd_V2f( frame1.position, mMul_f_V2f(-0.01, direction) );
// mGenerate_transform_2D(&frame1);
// mGenerate_transform_2D(&frame2);
// n_collisions = phDetect_Collisions(&rb_polygon_1, &rb_polygon_2, collisions);
// printf("%d Boolean test 5\n", n_collisions > 0 != true);
// for (int i= 0; i < n_collisions; i++) {
//   printf("\t%f\t%f\n", collisions[i].position.i[0], collisions[i].position.i[1]);
// }
