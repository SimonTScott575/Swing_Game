#ifndef GE_GAME_H
#define GE_GAME_H

#include <Game_Engine/geScene.h>
#include <Game_Engine/geInput_States.h>
#include <Game_Engine/geWindow.h>

typedef
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

} geGame;

// ===

void geSet_Active_Game(geGame* game);
geGame* geGet_Active_Game();

// ====================
// Creation/Destruction
// ====================

geGame* geCreate_Game(geWindow* window);

void geDestroy_Game(geGame* game);

// =========
// Start/End
// =========

// Plays scenes
void gePlay_Game(geGame* game);

void geEnd_Scene(geGame* game);
void geEnd_Game(geGame* game);

// ================
// Scene Management
// ================

// Add/remove scenes
void geAdd_Scene(geScene* scene, geGame* game);
void geAdd_Scene_Before(geScene* new_scene, geScene* scene2, geGame* game);
void geAdd_Scene_After(geScene* new_scene, geScene* scene2, geGame* game);

void geRemove_Scene(geScene* scene, geGame* game);

// Get scenes
geScene* geGet_First_Scene(geGame* game);
geScene* geGet_Next_Scene(geGame* game);

// Set next scene to be played, after scene ends the next scene will be the
// next scene in the order added.
void geSet_Next_Scene(geScene* scene, geGame* game);

// ===

void geSwap_Screens(geGame* game);

#endif
