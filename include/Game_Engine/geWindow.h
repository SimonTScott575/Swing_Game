//TODO: for multiple windows MUST properly implement active window changing opengl context
//TODO: remove grScreen and put with game, then use grActive_Screen OR grActive_Back/Front_Screen OR take back/front screens as arg in init

#ifndef GE_WINDOW_H
#define GE_WINDOW_H

#include <Game_Engine/dATUM/dLList.h>
#include <Game_Engine/Graphics/Graphics.h>

//? TEMP FORWARD HEADER
typedef struct GLFWwindow GLFWwindow;
typedef GLFWwindow* geWindow_ID;

typedef struct geWindow geWindow;

//
typedef void (*geCursor_Position_fn)(geWindow* window, double x, double y);

D_HEADER_LLIST(geCursor_Position_fn, geCursor_Position_fn);

typedef
struct geWindow {

  geWindow_ID _window_ID;

  int _X_pixels;
  int _Y_pixels;

  dLList(geCursor_Position_fn)* cursor_position_fns; // NOT IMPLEMENTED

} geWindow;

// =========================
// Initliazation/Termination
// =========================

geWindow* geCreate_Window(int width, int height, char* name);
void geDestroy_Window(geWindow* window);

// ===

geWindow* geGet_Active_Window();
void geSet_Active_Window(geWindow* window);

// ===

void geGet_Cursor_Position(geWindow* window, int* pos_pixel_x, int* pos_pixel_y);

// Set window should close property as true (retrive with geGet_Window_Should_Close)
void geSet_Window_Should_Close(geWindow* window, bool val);

// returns true if set as true by geSet_Window_Should_Close
bool geGet_Window_Should_Close(geWindow* window);

/*** LEGACY ***/
#define geWindow_Should_Close geGet_Window_Should_Close
/**************/

#endif
