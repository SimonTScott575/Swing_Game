//TODO: pass back/front screen to system
//TODO: swap screens NOT in "Render" fn but instead an "update system" fn (should make systems like other "classes")

#include <Game_Engine/Graphics/grRendering_System.h>

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/ge_common.h>
#include <Game_Engine/geWindow.h>

// ======
// static
// ======

static void grRender_Rendering_System2D_void(void* arg) {
  grRender_Rendering_System2D(arg);
}
static void grDestroy_Rendering_System2D_void(void* arg) {
  grDestroy_Rendering_System2D(arg);
}

// ====================
// Creation/Destruction
// ====================

grRendering_System2D* grCreate_Rendering_System2D(grCamera2D* camera) {

  grRendering_System2D* rs = malloc(sizeof(grRendering_System2D));
  if (rs == NULL) {
    GE_DEBUG_LOG("%s\n"
                 "Game_Engine DEBUG : Graphics/grRendering_System\n"
                 "                    rendering system malloc fail\n");
    return NULL;
  }

  *rs = (grRendering_System2D){
    ._super = geCreate_System(rs, grRender_Rendering_System2D_void, grDestroy_Rendering_System2D_void),
    .camera = camera,
    ._renderers = new_dLList(grRenderer_ptr)(0,NULL),
    .post_process = NULL
  };
  //TODO: handle super/renderers fail

  return rs;

}

void grDestroy_Rendering_System2D(grRendering_System2D* rs) {

  geDestroy_System(rs->_super);
  del_dLList(grRenderer_ptr)(rs->_renderers);

  free(rs);

}

// ===

void grRender_Rendering_System2D(grRendering_System2D* rs) {

  grScreen* screen = grGet_Active_Screen();

  rs->camera->_prepare(rs->camera, screen); // grPrepare_Camera(rs->camera, window->_back_screen);

  dNode_LL(grRenderer_ptr)* current = rs->_renderers->start;

  for (
    dNode_LL(grRenderer_ptr)* current = rs->_renderers->start;
    current != NULL;
    current = current->next
  ) {

    grRenderer* r = current->element;

    if (!geComponent_Is_Active(&r->_super)) { continue; }

    grRender(r, rs->camera);

  }

  if (rs->post_process != NULL) {
    rs->post_process(screen);
  }

}
