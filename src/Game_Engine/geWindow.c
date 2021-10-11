#include <Game_Engine/geWindow.h>

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

D_SOURCE_LLIST(geCursor_Position_fn, geCursor_Position_fn);

static geWindow* geActive_Window = NULL;

geWindow* geCreate_Window(int width, int height, char* name) {

  GLFWwindow* window_ID = glfwCreateWindow(width, height, name, NULL, NULL);
  if (window_ID == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate(); //? total termination a little too much ?
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

  if (geActive_Window == NULL) {
    geSet_Active_Window(window); //TEMP
  }

  return window;

}

void geDestroy_Window(geWindow* window) {

  glfwDestroyWindow(window->_window_ID);

  free(window);

}

geWindow* geGet_Active_Window() {
  return geActive_Window;
}

void geSet_Active_Window(geWindow* window) {
  geActive_Window = window;
}

bool geWindow_Should_Close(geWindow* window) {
  return glfwWindowShouldClose(window->_window_ID);
}
