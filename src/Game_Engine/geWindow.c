#include <Game_Engine/geWindow.h>

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

D_SOURCE_dLList(geCursor_Position_fn, geCursor_Position_fn);

static geWindow* geActive_Window = NULL;

geWindow* geCreate_Window(int width, int height, char* name) {

  GLFWwindow* window_ID = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window_ID == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent( window_ID );

  // Initialize GLAD
  if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
    printf("Failed to initialize GLAD\n");
    glfwTerminate();
  }

  geWindow* window = malloc(sizeof(geWindow));
  *window = (geWindow){
    ._window_ID = window_ID,
    ._X_pixels = width,
    ._Y_pixels = height,
    .cursor_position_fns = new_dLList(geCursor_Position_fn)(0,NULL)
  };

  window->_front_screen = malloc(sizeof(grScreen));
  window->_back_screen = malloc(sizeof(grScreen));
  *window->_front_screen = *window->_back_screen = (grScreen){
    ._colour_texture = NULL,

    ._clear_colour = { 0, 0, 0, 1 },
    ._clear_depth = 1,
    ._clear_stencil = 0,

    ._colour_mask = 15,
    ._depth_mask = 1,
    ._stencil_mask = 0xFFFFFFFF,

    ._stencil_test      = GL_ALWAYS,
    ._stencil_ref       = 0,
    ._stencil_test_mask = 0xFFFFFFFF,
    ._sFAIL       = GL_KEEP,
    ._sPASS_dFAIL = GL_KEEP,
    ._sPASS_dPASS = GL_KEEP,

    ._X_pixels = -1,
    ._Y_pixels = -1,

    ._OpenGL_ENABLED_FLAG = GL_COLOR_BUFFER_BIT,
    ._OpenGL_ID = 0
  };

  window->_front_screen->_colour_texture = NULL;
  window->_front_screen->_stencil_test = grTests.ALWAYS;
  window->_front_screen->_sFAIL       = grActions.KEEP;
  window->_front_screen->_sPASS_dFAIL = grActions.KEEP;
  window->_front_screen->_sPASS_dPASS = grActions.KEEP;
  window->_front_screen->_X_pixels = width;
  window->_front_screen->_Y_pixels = height;
  window->_back_screen->_colour_texture = NULL;
  window->_back_screen->_stencil_test = grTests.ALWAYS;
  window->_back_screen->_sFAIL       = grActions.KEEP;
  window->_back_screen->_sPASS_dFAIL = grActions.KEEP;
  window->_back_screen->_sPASS_dPASS = grActions.KEEP;
  window->_back_screen->_X_pixels = width;
  window->_back_screen->_Y_pixels = height;

  if (geActive_Window == NULL) {
    geSet_Active_Window(window); //TEMP
  }

  glfwSetFramebufferSizeCallback(window_ID, &geWindow_Resize_Callback);

  return window;

}

//!!! destroy

void geWindow_Resize_Callback(geWindow_ID window_ID, int width, int height) { //??? or with application
    glViewport(0, 0, width, height);

    geWindow* window = geGet_Active_Window(); //??? IS THIS FOR SURE THE ACTIVE WINDOW when multiple windows ? should actually search through array for matching id
    window->_X_pixels = width;
    window->_Y_pixels = height;
    window->_back_screen->_X_pixels = width;
    window->_back_screen->_Y_pixels = height;
    window->_front_screen->_X_pixels = width;
    window->_front_screen->_Y_pixels = height;
}

geWindow* geGet_Active_Window() {
  return geActive_Window;
}

void geSet_Active_Window(geWindow* window) {
  //... to change opengl context
  geActive_Window = window;
  grSet_Active_Screen(window->_back_screen);
}

bool geWindow_Should_Close(geWindow* window) {
  return glfwWindowShouldClose(window->_window_ID);
}

void geSwap_Screens(geWindow* window) {

  grScreen* screen_A = window->_back_screen;
  window->_back_screen = window->_front_screen;
  window->_front_screen = screen_A;

  glfwSwapBuffers(window->_window_ID);

}
