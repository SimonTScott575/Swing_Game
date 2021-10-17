#include <Game_Engine/UI/Defaults/geUI_Manager.h>

#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/ECS/geEntity.h>

// ==========================
// Initialization/Termiantion
// ==========================

geUI_Manager* geCreate_UI_Manager(grCamera2D* camera) {

  geUI_Manager* uim = malloc(sizeof(geUI_Manager));

  geSystem* system = geCreate_System(uim, geUpdate_UI_Manager, geDestroy_UI_Manager);

  *uim = (geUI_Manager){
    ._super = system,
    .camera = camera,
    ._elements = new_dLList(geUI_Element_ptr)(0, NULL)
  };

  return uim;

}

void geDestroy_UI_Manager(void* arg) {

  geUI_Manager* uim = arg;

  geDestroy_System(uim->_super);

  del_dLList(geUI_Element_ptr)(uim->_elements);

  free(uim);

}

// ===

void geUpdate_UI_Manager(void* arg) {

  geUI_Manager* uim = arg;

  bool is_down = glfwGetMouseButton(geGet_Active_Window()->_window_ID, GLFW_MOUSE_BUTTON_LEFT);
  double mouse_X;
  double mouse_Y;
  glfwGetCursorPos(geGet_Active_Window()->_window_ID, &mouse_X, &mouse_Y);

  float normalized_mouse_X = mouse_X/geGet_Active_Window()->_X_pixels*2 - 1;
  float normalized_mouse_Y = (1 - mouse_Y/geGet_Active_Window()->_Y_pixels)*2 - 1;

  for ( dNode_LL(geUI_Element_ptr)* uie_node = uim->_elements->start;
        uie_node != NULL;
        uie_node = uie_node->next ) {

    geUI_Element* uie = uie_node->element;

    if (!geComponent_Is_Active(&uie->_super)) { continue; }

    geUpdate_UI_Element(uie, uim->camera->_X_length, normalized_mouse_X, normalized_mouse_Y, geGet_Active_Window());

  }

  float inv_ar = (float)geGet_Active_Window()->_X_pixels/geGet_Active_Window()->_Y_pixels;
  grSet_Projection_2D(2*inv_ar, 2, uim->camera); //? at top ?

}
