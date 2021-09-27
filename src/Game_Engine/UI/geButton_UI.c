#include <Game_Engine/UI/geButton_UI.h>

#include <Game_Engine/geGame.h>
#include <Game_Engine/geInput.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// static void geDestroy_UI_Element_void(void* uie) {
//   geDestroy_UI_Element(uie);
// }

geButton_UI* geCreate_Button_UI(float x_length, float y_length, mFrame2D* frame) {

  geButton_UI* button = malloc(sizeof(geButton_UI));

  *button = (geButton_UI){
    ._super = init_geUI_Element(frame),
    .x_length = x_length,
    .y_length = y_length
  };

  geSet_Sub_UI_Element(button, geUpdate_Button_UI, geDestroy_Button_Sub_UI_Element, &button->_super);

  button->_super._super = geCreate_Component();
  geSet_Sub_Component(&button->_super, NULL, geDestroy_UI_Element_Sub_Component, button->_super._super);

  return button;

}

void geDestroy_Button_Sub_UI_Element(geUI_Element* uie) {

  geButton_UI* button = uie->_sub;

  free(button);

}

void geUpdate_Button_UI(geUI_Element* uie, float x_length, float mouse_X, float mouse_Y, geWindow* window) {

  geButton_UI* button = uie->_sub;

  if (button->on_click == NULL) { return; }

  mVector2f normalized_centre = (mVector2f){{
    uie->x + uie->frame->position.i[0]/x_length * 2,
    uie->y + uie->frame->position.i[1]
  }};
  float normalized_x_length = button->x_length/x_length * 2;
  float normalized_y_length = button->y_length;

  if (   normalized_centre.i[0] - normalized_x_length/2 < mouse_X && mouse_X < normalized_centre.i[0] + normalized_x_length/2
      && normalized_centre.i[1] - normalized_y_length/2 < mouse_Y && mouse_Y < normalized_centre.i[1] + normalized_y_length/2) {

    if (geMouse_Button_Down_Stroke(geGet_Active_Game(), GLFW_MOUSE_BUTTON_LEFT)) { //? better if geGet_Active_Input_States() ?
      button->on_click(uie);
    }
  }

}
