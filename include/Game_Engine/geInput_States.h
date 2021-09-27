#ifndef GE_INPUT_STATES_H
#define GE_INPUT_STATES_H

#include <stdint.h>

// #include "../../extern/glad/glad.h"
// #include "../../extern/GLFW/glfw3.h"

#define GE_KEY_STATES_LENGTH 348
#define GE_MOUSE_STATES_LENGTH 7

// #define GE_KEY_UP          0
// #define GE_KEY_DOWN        1
#define GE_KEY_DOWN_STROKE 2
#define GE_KEY_UP_STROKE   4

// FORWARD HEADER
typedef struct GLFWwindow GLFWwindow;

typedef struct geInput_States geInput_States;

struct geInput_States {
  uint8_t states[GE_KEY_STATES_LENGTH+1];
  uint8_t mouse_states[GE_MOUSE_STATES_LENGTH+1];
};

void geSet_Active_Input_States(geInput_States* input_states);

void geSet_Input_States_ZERO(geInput_States* states);

void geKey_States_Callback_GLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
void geMouse_Button_Callback_GLFW(GLFWwindow* window, int button, int action, int mods);

#endif
