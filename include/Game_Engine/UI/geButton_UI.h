#ifndef GE_BUTTON_UI_H
#define GE_BUTTON_UI_H

#include <Game_Engine/geWindow.h>

#include "geUI_Element.h"

typedef struct geButton_UI geButton_UI;

typedef void (*geOn_Click_fn)(geUI_Element* element);

struct geButton_UI {

  geUI_Element _super;

  float x_length;
  float y_length;
  geOn_Click_fn on_click;

};

void geButton_UI_ctor(geButton_UI* self, float x_length, float y_length, mFrame2D* frame); //! no renderer needed with ui_r

void geUpdate_Button_UI(geUI_Element* uie, float x_length, float mouse_X, float mouse_Y, geWindow* window);

#endif
