#include <Game_Engine/geGame.h>

#include <Game_Engine/ge_common.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/Game_Engine.h>

// ======
// static
// ======

static geGame* geActive_Game = NULL;

static void geWindow_Resize_Callback(geWindow_ID window_ID, int width, int height);

// ====================
// Creation/Destruction
// ====================

geGame* geCreate_Game(geWindow* window) {

  geGame* game = malloc(sizeof(geGame));
  if (game == NULL) {
    goto catch_game_malloc_fail;
  }

  *game = (geGame){
    ._active_scene = NULL,
    ._end_scene = false,
    ._end_game = false,

    ._next_scene = NULL,

    ._scenes = new_dLList(geScene_ptr)(0, NULL),

    .time = 0,
    .delta_time = 0,

    .input_states = (geInput_States){0},

    .window = window
  };

  // set screen data
  game->_back_screen = malloc(sizeof(grScreen));
  if (game->_back_screen == NULL) { goto catch_back_screen_fail; }
  game->_front_screen = malloc(sizeof(grScreen));
  if (game->_front_screen == NULL) { goto catch_front_screen_fail; }

  *game->_front_screen = *game->_back_screen = (grScreen){ //? grScreen_ctor ?
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

  game->_front_screen->_colour_texture = NULL;
  game->_front_screen->_stencil_test = grTests.ALWAYS;
  game->_front_screen->_sFAIL       = grActions.KEEP;
  game->_front_screen->_sPASS_dFAIL = grActions.KEEP;
  game->_front_screen->_sPASS_dPASS = grActions.KEEP;
  game->_front_screen->_X_pixels = window->_X_pixels;
  game->_front_screen->_Y_pixels = window->_Y_pixels;
  game->_back_screen->_colour_texture = NULL;
  game->_back_screen->_stencil_test = grTests.ALWAYS;
  game->_back_screen->_sFAIL       = grActions.KEEP;
  game->_back_screen->_sPASS_dFAIL = grActions.KEEP;
  game->_back_screen->_sPASS_dPASS = grActions.KEEP;
  game->_back_screen->_X_pixels = window->_X_pixels;
  game->_back_screen->_Y_pixels = window->_Y_pixels;

  // set callbacks - window resize and input
  glfwSetFramebufferSizeCallback(window->_window_ID, &geWindow_Resize_Callback);

  glfwSetKeyCallback(window->_window_ID, geKey_States_Callback_GLFW); //TODO: make geSet_Input_Callback(geWindow_ID*, callback fn);
  glfwSetMouseButtonCallback(window->_window_ID, geMouse_Button_Callback_GLFW); //TODO: make geSet_Input_Callback(geWindow_ID*, callback fn);

  //
  if ( geGet_Active_Game() == NULL ) {
    geSet_Active_Game(game);
  }

  goto no_catch;

  catch_front_screen_fail :
    free(game->_back_screen);
    GE_DEBUG_LOG("\n%s",
                 "Game_Engine DEBUG : geGame\n"
                 "                    malloc fail\n");
  catch_back_screen_fail :
    free(game);
    GE_DEBUG_LOG("\n%s",
                 "Game_Engine DEBUG : geGame\n"
                 "                    malloc fail\n");
  catch_game_malloc_fail :
   GE_DEBUG_LOG("\n%s",
                "Game_Engine DEBUG : geGame\n"
                "                    malloc fail\n");
  return NULL;

  no_catch:

  return game;

}

void geDestroy_Game(geGame* game) {

  del_dLList(geScene_ptr)(game->_scenes);

  free(game);

}

// ======
// Active
// ======

void geSet_Active_Game(geGame* game) {

  geSet_Active_Window(game->window);
  geSet_Active_Input_States(&game->input_states);
  grSet_Active_Screen(game->_back_screen); //... to change opengl context

  geActive_Game = game;

}
geGame* geGet_Active_Game() {
  return geActive_Game;
}

// ===

void gePlay_Game(geGame* game) {

  game->_active_scene = geGet_Next_Scene(game);
  if (game->_active_scene == NULL) { return; }

  game->_end_game = false;
  game->_end_scene = false;

  float start_time = glfwGetTime();
  game->time = 0;
  game->delta_time = 0;

  while (!game->_end_game && !geWindow_Should_Close(game->window)) {

    if ( !game->_active_scene->_is_loaded ) {
      geLoad_Scene(game->_active_scene);
    }
    game->delta_time = glfwGetTime() - start_time - game->time;

    if (    !(game->_end_scene || game->_end_game)
         && game->delta_time > 0.02 ) {

      grSet_Active_Screen(game->_back_screen); //?
      geUpdate_Scene(game->_active_scene);

      geSwap_Screens(game);
      geProcess_Events();

      game->time += game->delta_time;

    }

    if (game->_end_scene || game->_end_game) {

      geUnload_Scene(game->_active_scene);

      game->_active_scene = geGet_Next_Scene(game);
      game->_next_scene = NULL;

      if (game->_active_scene == NULL) {
        game->_end_game = true;
      }

      game->_end_scene = false;

    }

  }

  game->_active_scene = NULL;
  game->_next_scene = NULL;
  game->_end_scene = false;
  game->_end_game = false;

}

void geEnd_Scene(geGame* game) {

  game->_end_scene = true;

}

void geEnd_Game(geGame* game) {

  game->_end_game = true;

}

// ===

void geAdd_Scene(geScene* scene, geGame* game) {
  scene->_scene_node = dAppend_LL(geScene_ptr)(scene, game->_scenes);
}
void geAdd_Scene_Before(geScene* new_scene, geScene* scene2, geGame* game) {
  new_scene->_scene_node = dInsert_Before_LL(geScene_ptr)(new_scene, scene2->_scene_node, game->_scenes);
}
void geAdd_Scene_After(geScene* new_scene, geScene* scene2, geGame* game) {
  new_scene->_scene_node = dInsert_After_LL(geScene_ptr)(new_scene, scene2->_scene_node, game->_scenes);
}

void geRemove_Scene(geScene* scene, geGame* game) {
  dRemove_LL(geScene_ptr)(scene->_scene_node, game->_scenes);
  scene->_scene_node = NULL;
}

geScene* geGet_First_Scene(geGame* game) {

  if (game->_scenes == NULL || game->_scenes->start == NULL) {
    return NULL;
  }

  return game->_scenes->start->element;

}
geScene* geGet_Next_Scene(geGame* game) {

  if (game->_next_scene != NULL) {
    return game->_next_scene;
  }

  if (game->_active_scene == NULL) {
    return geGet_First_Scene(game);
  }

  if (    game->_active_scene->_scene_node != NULL
       && game->_active_scene->_scene_node->next != NULL ) {
    return game->_active_scene->_scene_node->next->element;
  }

  return NULL;

}
void geSet_Next_Scene(geScene* scene, geGame* game) {

  game->_next_scene = scene;

}

// ===

static void geWindow_Resize_Callback(geWindow_ID window_ID, int width, int height) { //??? or with application
    glViewport(0, 0, width, height);

    geWindow* window = geGet_Active_Window(); //??? IS THIS FOR SURE THE ACTIVE WINDOW when multiple windows ? should actually search through array for matching id
    window->_X_pixels = width;
    window->_Y_pixels = height;
    geGet_Active_Game()->_back_screen->_X_pixels = width; //? again, active window or ???
    geGet_Active_Game()->_back_screen->_Y_pixels = height;
    geGet_Active_Game()->_front_screen->_X_pixels = width;
    geGet_Active_Game()->_front_screen->_Y_pixels = height;
}

void geSwap_Screens(geGame* game) {

  grScreen* screen_A = game->_back_screen;
  game->_back_screen = game->_front_screen;
  game->_front_screen = screen_A;

  glfwSwapBuffers(game->window->_window_ID);

}
