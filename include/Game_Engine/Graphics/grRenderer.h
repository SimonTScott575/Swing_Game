#ifndef GR_RENDERER_H
#define GR_RENDERER_H

#include <stdbool.h>

#include <Game_Engine/ECS/geComponent.h>

#include <Game_Engine/dATUM/dLList.h>
#include <Game_Engine/Maths/mFrame.h>

#include "grShader.h"
#include "grModel.h"
#include "Defaults/grCamera.h"

typedef struct grRenderer grRenderer;
typedef void (*grRender_fn)(grRenderer* renderer, grCamera2D* camera);
typedef void (*grDestroy_Sub_Renderer_fn)(grRenderer* renderer);

D_HEADER_dLList(grRenderer*, grRenderer_ptr);

struct grRenderer {

  geComponent* _super;

  bool is_active;
  dNode_LL(grRenderer_ptr)* _renderer_node;

  grRender_fn render_fn;

  void* frame;
  grModel* model;
  grShader* shader;

  float Z;

  grDestroy_Sub_Renderer_fn _destroy_sub;
  void* _sub;

};

// ====================
// Creation/Destruction
// ====================

// Creates renderer for 2D or 3D rendering respectively
grRenderer* grCreate_Renderer_2D(mFrame2D* frame, grModel* model, grShader* shader);
grRenderer* grCreate_Renderer_3D(mFrame3D* frame, grModel* model, grShader* shader);

// void grDestroy_Renderer(grRenderer* renderer);

void grDestroy_Renderer_Sub_Component(geComponent* component);

// ===

void grSet_Sub_Renderer(void* sub, grDestroy_Sub_Renderer_fn destroy_sub_fn, grRenderer* renderer);

// ======
// Render
// ======

// ONLY call when renderer->frame holds mFrame2D
void grRender_2D(grRenderer* renderer, grCamera2D* camera);
// // ONLY call when renderer->frame holds mFrame3D
// void grRender_3D(grRenderer* renderer, grCamera2D* camera);

// Draws to ... //?
void grRender(grRenderer* renderer, grCamera2D* camera);

#endif
