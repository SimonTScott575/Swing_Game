#include <Game_Engine/geWindow.h>

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/ge_common.h>

D_SOURCE_LLIST(geCursor_Position_fn, geCursor_Position_fn);

// ======
// static
// ======

static geWindow* geActive_Window = NULL;

// =========================
// Initliazation/Termination
// =========================

geWindow* geCreate_Window(int width, int height, char* name) {

  GLFWwindow* window_ID = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window_ID == NULL) {
    GE_DEBUG_LOG("%s\n",
                 "Game_Engine DEBUG : geWindow\n"
                 "                    glfwCreateWindow fail\n");
    return NULL;
  }

  glfwMakeContextCurrent( window_ID );

  // Initialize GLAD
  if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
    GE_DEBUG_LOG("%s\n",
                 "Game_Engine DEBUG : geWindow\n"
                 "                    gladLoadGLLoader fail\n");
    glfwDestroyWindow(window_ID);
    return NULL;
  }

  geWindow* window = malloc(sizeof(geWindow));
  if (window == NULL) {
    GE_DEBUG_LOG("%s\n",
                 "Game_Engine DEBUG : geWindow\n"
                 "                    window malloc fail\n");
    glfwDestroyWindow(window_ID);
    return NULL;
  }
  *window = (geWindow){
    ._window_ID = window_ID,
    .cursor_position_fns = new_dLList(geCursor_Position_fn)(0,NULL)
  };
  glfwGetFramebufferSize(window->_window_ID, &window->_X_pixels, &window->_Y_pixels);

  if (geActive_Window == NULL) {
    geSet_Active_Window(window);
  }

  grInit();

  return window;

}

void geDestroy_Window(geWindow* window) {

  glfwDestroyWindow(window->_window_ID);

  free(window);

}

// ===

geWindow* geGet_Active_Window() {
  return geActive_Window;
}

void geSet_Active_Window(geWindow* window) {
  geActive_Window = window;
}

// ===

void geGet_Cursor_Position(geWindow* window, int* pos_pixel_x, int* pos_pixel_y) {

  int size_screen_x;
  int size_screen_y;
  glfwGetWindowSize(window->_window_ID, &size_screen_x, &size_screen_y);

  double pos_screen_x;
  double pos_screen_y;
  glfwGetCursorPos(window->_window_ID, &pos_screen_x, &pos_screen_y);

  *pos_pixel_x = window->_X_pixels * (pos_screen_x/size_screen_x);
  *pos_pixel_y = window->_Y_pixels * (pos_screen_y/size_screen_y);

}

#if GLFW_TRUE != 1
  #error GLFW_TRUE not set to 1
#endif
#if GLFW_FALSE != 0
  #error GLFW_FALSE not set to 0
#endif

void geSet_Window_Should_Close(geWindow* window, bool val) {
  glfwSetWindowShouldClose(window->_window_ID, val);
}
bool geGet_Window_Should_Close(geWindow* window) {
  return glfwWindowShouldClose(window->_window_ID);
}
