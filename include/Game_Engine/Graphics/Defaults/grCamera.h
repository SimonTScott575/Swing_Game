#ifndef GR_CAMERA_H
#define GR_CAMERA_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/Maths/Maths.h>

#include <Game_Engine/ECS/geComponent.h>

typedef struct grCamera2D grCamera2D;
typedef struct grCamera3D grCamera3D;

struct grCamera2D {

  geComponent* _super;

  mFrame2D* frame;

  float _X_length;

  mMatrix3f View3x3;
  mMatrix3f Projection3x3;

  float background_colour[4];

};
// struct grCamera3D {
//
//   geComponent* _super;
//
//   mFrame3D* frame;
//
//   mMatrix4f View4x4;
//   mMatrix4f Projection4x4;
//
//   float background_colour[4];
//
//
// };

// ====================
// Creation/Destruction
// ====================

grCamera2D* grCreate_Camera2D(mFrame2D* frame, float width, float height);
// grCamera3D* grCreate_Camera3D(mFrame3D* frame, float width, float height, float near_dist, float far_dist);

// void grDestroy_Camera2D(grCamera2D* camera);
// void grDestroy_Camera3D(grCamera3D* camera);

void grDestroy_Camera2D_Sub_Component(geComponent* component);

// ========================
// View/Projection Matrices
// ========================

void grSet_View_2D(mFrame2D* frame, grCamera2D* camera);
// void grSet_View_3D(mFrame3D* frame, grCamera3D* camera);

void grSet_Projection_2D(float width, float height, grCamera2D* camera);
// void grSet_Projection_3D(float width, float height, float near_dist, float far_dist, bool as_orthographic, grCamera3D* camera);

#endif
