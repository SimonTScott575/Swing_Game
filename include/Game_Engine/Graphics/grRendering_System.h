#ifndef GR_RENDERING_SYSTEM
#define GR_RENDERING_SYSTEM

#include <Game_Engine/ECS/geSystem.h>
#include <Game_Engine/ECS/geEntity.h>

#include <Game_Engine/Graphics/grRenderer.h>
#include <Game_Engine/Graphics/grScreen.h>
#include <Game_Engine/Graphics/grCamera.h>

typedef struct grRendering_System2D grRendering_System2D;

typedef void (*grPost_Processing_fn)(grScreen* screen);

typedef
struct grRendering_System2D {

  geSystem* _super;

  grCamera2D* camera;
  dLList(grRenderer_ptr)* _renderers;

  grPost_Processing_fn post_process;

} grRendering_System2D;

// ====================
// Creation/Destruction
// ====================

grRendering_System2D* grCreate_Rendering_System2D(grCamera2D* camera);

void grDestroy_Rendering_System2D(grRendering_System2D* rs);

// ===

void grRender_Rendering_System2D(grRendering_System2D* rs);

void grSet_Post_Processing(grPost_Processing_fn p, grRendering_System2D* rs);

#endif
