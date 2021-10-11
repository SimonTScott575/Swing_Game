#ifndef GE_GAME_H
#define GE_GAME_H

#include <Game_Engine/geScene.h>
#include <Game_Engine/geInput_States.h>
#include <Game_Engine/geWindow.h>

typedef struct geGame geGame;

struct geGame {

  geScene* _active_scene;
  bool _end_scene;
  bool _end_game;

  geScene* _next_scene;

  float time;
  float delta_time;

  dLList(geScene_ptr)* _scenes;

  geInput_States input_states;

  grScreen* _front_screen;
  grScreen* _back_screen;

  geWindow* window;

};

// ===

void geSet_Active_Game(geGame* game);
geGame* geGet_Active_Game();

// ====================
// Creation/Destruction
// ====================

geGame* geCreate_Game(geWindow* window);

void geDestroy_Game(geGame* game);

// ===

void geUnload_Game(geGame* game); //? what about already unloaded scenes ? static ?

void gePlay_Game(geGame* game);

void geEnd_Scene(geGame* game);
void geEnd_Game(geGame* game);

//? end_game used instead of unload game ? or end_game used by components to signal end ?

// ===

void geAdd_Scene(geScene* scene, geGame* game);
void geAdd_Scene_Before(geScene* new_scene, geScene* scene2, geGame* game);
void geAdd_Scene_After(geScene* new_scene, geScene* scene2, geGame* game);

void geRemove_Scene(geScene* scene, geGame* game);

geScene* geGet_First_Scene(geGame* game);

geScene* geGet_Next_Scene(geGame* game);
void geSet_Next_Scene(geScene* scene, geGame* game);

void geSwap_Screens(geGame* game);

// void geAdd_Scene(geScene* scene, geGame* game);
// void geRemove_Scene(geScene* scene, geGame* game);

#endif
