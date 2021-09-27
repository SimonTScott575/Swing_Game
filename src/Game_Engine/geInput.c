#include <Game_Engine/geInput.h>

// =======
// Getters
// =======

bool geKey_Down_Stroke(geGame* game, int key) {

  return game->input_states.states[key] & GE_KEY_DOWN_STROKE;

}
bool geKey_Up_Stroke(geGame* game, int key) {

  return game->input_states.states[key] & GE_KEY_UP_STROKE;

}

bool geMouse_Button_Down_Stroke(geGame* game, int button) {

  return game->input_states.mouse_states[button] & GE_KEY_DOWN_STROKE;

}
bool geMouse_Button_Up_Stroke(geGame* game, int button) {

  return game->input_states.mouse_states[button] & GE_KEY_UP_STROKE;

}
