//TODO: for multiple windows MUST properly implement active window changing opengl context

#ifndef GE_WINDOW_H
#define GE_WINDOW_H

#include <Game_Engine/dATUM/dLList.h>

#include <Game_Engine/Graphics/grScreen.h>

//TEMP FORWARD HEADER //?
typedef struct GLFWwindow GLFWwindow;
typedef GLFWwindow* geWindow_ID;

typedef struct geWindow geWindow;

typedef void (*geCursor_Position_fn)(geWindow* window, double x, double y);

D_HEADER_dLList(geCursor_Position_fn, geCursor_Position_fn);

struct geWindow {

  geWindow_ID _window_ID;

  int _X_pixels;
  int _Y_pixels;

  grScreen* _front_screen;
  grScreen* _back_screen;

  dLList(geCursor_Position_fn)* cursor_position_fns; // NOT IMPLEMENTED

};

geWindow* geCreate_Window(int width, int height, char* name);
//!!! destroy

void geWindow_Resize_Callback(geWindow_ID window_ID, int width, int height); //TEMP, shouldn't be public

geWindow* geGet_Active_Window();

void geSet_Active_Window(geWindow* window);

bool geWindow_Should_Close(geWindow* window);

void geSwap_Screens(geWindow* window);

#endif
