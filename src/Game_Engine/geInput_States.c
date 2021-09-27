#include <Game_Engine/geInput_States.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if GLFW_KEY_LAST != GE_KEY_STATES_LENGTH || GLFW_MOUSE_BUTTON_LAST != GE_MOUSE_STATES_LENGTH
  #error GE STATES LENGTH NOT SET CORRECTLY
#endif

// ======
// static
// ======

static geInput_States* active_input_states = NULL;

// ========
// Settters
// ========

void geSet_Active_Input_States(geInput_States* input_states) {
  active_input_states = input_states;
}

void geSet_Input_States_ZERO(geInput_States* states) { //? rename for key_down/up only case ?
  *states = (geInput_States){0};
}

// ===

void geKey_States_Callback_GLFW(GLFWwindow* window, int key, int scancode, int action, int mods) {

  if (key > GLFW_KEY_LAST) { return; }
  if (active_input_states == NULL) { return; }

  if (action == GLFW_PRESS) {
    active_input_states->states[key] = GE_KEY_DOWN_STROKE;
  } else if (action == GLFW_RELEASE) {
    active_input_states->states[key] = GE_KEY_UP_STROKE;
  }

}

void geMouse_Button_Callback_GLFW(GLFWwindow* window, int button, int action, int mods) {

  if (button > GLFW_MOUSE_BUTTON_LAST) { return; }
  if (active_input_states == NULL) { return; }

  if (action == GLFW_PRESS) {
    active_input_states->mouse_states[button] = GE_KEY_DOWN_STROKE;
  } else if (action == GLFW_RELEASE) {
    active_input_states->mouse_states[button] = GE_KEY_UP_STROKE;
  }

}
