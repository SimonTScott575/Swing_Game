#include <Game_Engine/Graphics/Defaults/grRendering_System.h>

#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/geWindow.h>

//

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

  *rs = (grRendering_System2D){
    ._super = geCreate_System(rs, grRender_Rendering_System2D_void, grDestroy_Rendering_System2D_void),
    .camera = camera,
    ._renderers = new_dLList(grRenderer_ptr)(0,NULL),
    .post_process = NULL
  };

  return rs;

}

void grDestroy_Rendering_System2D(grRendering_System2D* rs) {

  geDestroy_System(rs->_super);
  del_dLList(grRenderer_ptr)(rs->_renderers);

  free(rs);

}

// ===

void grRender_Rendering_System2D(grRendering_System2D* rs) {

  geWindow* window = geGet_Active_Window(); //! change to screen!
  // grSet_Projection_2D(rs->camera->_X_length, (float)window->_Y_pixels/window->_X_pixels * rs->camera->_X_length, rs->camera); //? do by user, not GE ?

  grSet_View_2D(rs->camera->frame, rs->camera);
  grSet_Clear_Screen_Colour(rs->camera->background_colour, window->_back_screen);
  if (rs->camera->background_colour[3] != 0) {
    grClear_Screen(window->_back_screen);
  }

  dNode_LL(grRenderer_ptr)* current = rs->_renderers->start;

  for ( ; current != NULL; current = current->next ) {

    if (!current->element->is_active) { continue; }
    if (current->element->_super != NULL && !current->element->_super->is_active) { continue; }
    if (current->element->_super != NULL && current->element->_super->_entity != NULL && !current->element->_super->_entity->is_active) { continue; }

    // mGenerate_transform_2D((mFrame2D*) current->element->frame);
    grRender(current->element, rs->camera);

  }

  if (rs->post_process != NULL) {
    rs->post_process(window->_back_screen);
  }

  // geSwap_Screens(geGet_Active_Window());

}
