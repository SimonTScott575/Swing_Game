#ifndef GR_CAMERA_H
#define GR_CAMERA_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/Maths/Maths.h>
#include <Game_Engine/ECS/geComponent.h>

#include <Game_Engine/Graphics/grScreen.h>

typedef struct grCamera2D grCamera2D;
typedef struct grCamera3D grCamera3D;

typedef void (*grPrepare_Camera_fn)(grCamera2D* camera, grScreen* screen);

struct grCamera2D {

  geComponent* _super;

  mFrame2D* frame;

  float _X_length;

  mMatrix3f View3x3;
  mMatrix3f Projection3x3;

  float background_colour[4];

  void* _sub;
  grPrepare_Camera_fn _prepare;

};

// ====================
// Creation/Destruction
// ====================

grCamera2D* grCreate_Camera2D(mFrame2D* frame, float width, float height);

void grDestroy_Camera2D_Sub_Component(geComponent* component);

void grSet_Sub_Camera2D(void* sub, grPrepare_Camera_fn prepare, grCamera2D* camera);

// ========================
// View/Projection Matrices
// ========================

void grSet_View_2D(mFrame2D* frame, grCamera2D* camera);

void grSet_Projection_2D(float width, float height, grCamera2D* camera);

// ===

void grPrepare_Camera(grCamera2D* camera, grScreen* screen);

#endif
