#include <Game_Engine/geGame.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/Game_Engine.h>

// ======
// static
// ======

static geGame* geActive_Game = NULL;

// ======
// global//?
// ======

void geSet_Active_Game(geGame* game) {

  geSet_Active_Input_States(&game->input_states);

  geActive_Game = game;

}
geGame* geGet_Active_Game() {
  return geActive_Game;
}

// ====================
// Creation/Destruction
// ====================

geGame* geCreate_Game(geWindow* window) {

  geGame* game = malloc(sizeof(geGame));

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

  glfwSetKeyCallback(window->_window_ID, geKey_States_Callback_GLFW);
  glfwSetMouseButtonCallback(window->_window_ID, geMouse_Button_Callback_GLFW);

  if ( geGet_Active_Game() == NULL ) {
    geSet_Active_Game(game);
  }

  return game;

}

void geDestroy_Game(geGame* game) {

  del_dLList(geScene_ptr)(game->_scenes);

  free(game);

}

// ===

void geUnload_Game(geGame* game) {

  dNode_LL(geScene_ptr)* scene_node = game->_scenes->start;

  while (scene_node != NULL) {

    geUnload_Scene(scene_node->element); //??? what if scene already unloaded ? as will be the case ...

    scene_node = scene_node->next;

  }

  geDestroy_Game(game); //??? NO

}

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

    if ( game->delta_time > 0.02 ) {

      geUpdate_Scene(game->_active_scene);

      geSwap_Screens(game->window);
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

// ===

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






// void geAdd_Scene(geScene* scene, geGame* game) {
//   scene->_scene_node = dAppend_LLScene(scene, game->_scenes);
//
//   if (game->_active_scene == NULL) {
//     game->_active_scene = scene;
//   }
// }
//
// void geRemove_Scene(geScene* scene, geGame* game) {
//   dRemove_LLScene(scene->_scene_node, game->_scenes);
//
//   if (game->_active_scene == scene) {
//     game->_active_scene == NULL;
//   }
// }
