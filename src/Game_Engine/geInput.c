#include <Game_Engine/geInput.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if    GLFW_KEY_UNKNOWN != GE_KB_UNKNOWN \
    || GLFW_KEY_SPACE != GE_KB_SPACE \
    || GLFW_KEY_APOSTROPHE != GE_KB_APOSTROPHE \
    || GLFW_KEY_COMMA != GE_KB_COMMA \
    || GLFW_KEY_MINUS != GE_KB_MINUS \
    || GLFW_KEY_PERIOD != GE_KB_PERIOD \
    || GLFW_KEY_SLASH != GE_KB_SLASH \
    || GLFW_KEY_0 != GE_KB_0 \
    || GLFW_KEY_1 != GE_KB_1 \
    || GLFW_KEY_2 != GE_KB_2 \
    || GLFW_KEY_3 != GE_KB_3 \
    || GLFW_KEY_4 != GE_KB_4 \
    || GLFW_KEY_5 != GE_KB_5 \
    || GLFW_KEY_6 != GE_KB_6 \
    || GLFW_KEY_7 != GE_KB_7 \
    || GLFW_KEY_8 != GE_KB_8 \
    || GLFW_KEY_9 != GE_KB_9 \
    || GLFW_KEY_SEMICOLON != GE_KB_SEMICOLON \
    || GLFW_KEY_EQUAL != GE_KB_EQUAL \
    || GLFW_KEY_A != GE_KB_A \
    || GLFW_KEY_B != GE_KB_B \
    || GLFW_KEY_C != GE_KB_C \
    || GLFW_KEY_D != GE_KB_D \
    || GLFW_KEY_E != GE_KB_E \
    || GLFW_KEY_F != GE_KB_F \
    || GLFW_KEY_G != GE_KB_G \
    || GLFW_KEY_H != GE_KB_H \
    || GLFW_KEY_I != GE_KB_I \
    || GLFW_KEY_J != GE_KB_J \
    || GLFW_KEY_K != GE_KB_K \
    || GLFW_KEY_L != GE_KB_L \
    || GLFW_KEY_M != GE_KB_M \
    || GLFW_KEY_N != GE_KB_N \
    || GLFW_KEY_O != GE_KB_O \
    || GLFW_KEY_P != GE_KB_P \
    || GLFW_KEY_Q != GE_KB_Q \
    || GLFW_KEY_R != GE_KB_R \
    || GLFW_KEY_S != GE_KB_S \
    || GLFW_KEY_T != GE_KB_T \
    || GLFW_KEY_U != GE_KB_U \
    || GLFW_KEY_V != GE_KB_V \
    || GLFW_KEY_W != GE_KB_W \
    || GLFW_KEY_X != GE_KB_X \
    || GLFW_KEY_Y != GE_KB_Y \
    || GLFW_KEY_Z != GE_KB_Z \
    || GLFW_KEY_LEFT_BRACKET != GE_KB_LEFT_BRACKET \
    || GLFW_KEY_BACKSLASH != GE_KB_BACKSLASH \
    || GLFW_KEY_RIGHT_BRACKET != GE_KB_RIGHT_BRACKET \
    || GLFW_KEY_GRAVE_ACCENT != GE_KB_GRAVE_ACCENT \
    || GLFW_KEY_WORLD_1 != GE_KB_WORLD_1 \
    || GLFW_KEY_WORLD_2 != GE_KB_WORLD_2 \
    || GLFW_KEY_ESCAPE != GE_KB_ESCAPE \
    || GLFW_KEY_ENTER != GE_KB_ENTER \
    || GLFW_KEY_TAB != GE_KB_TAB \
    || GLFW_KEY_BACKSPACE != GE_KB_BACKSPACE \
    || GLFW_KEY_INSERT != GE_KB_INSERT \
    || GLFW_KEY_DELETE != GE_KB_DELETE \
    || GLFW_KEY_RIGHT != GE_KB_RIGHT \
    || GLFW_KEY_LEFT != GE_KB_LEFT \
    || GLFW_KEY_DOWN != GE_KB_DOWN \
    || GLFW_KEY_UP != GE_KB_UP \
    || GLFW_KEY_PAGE_UP != GE_KB_PAGE_UP \
    || GLFW_KEY_PAGE_DOWN != GE_KB_PAGE_DOWN \
    || GLFW_KEY_HOME != GE_KB_HOME \
    || GLFW_KEY_END != GE_KB_END \
    || GLFW_KEY_CAPS_LOCK != GE_KB_CAPS_LOCK \
    || GLFW_KEY_SCROLL_LOCK != GE_KB_SCROLL_LOCK \
    || GLFW_KEY_NUM_LOCK != GE_KB_NUM_LOCK \
    || GLFW_KEY_PRINT_SCREEN != GE_KB_PRINT_SCREEN \
    || GLFW_KEY_PAUSE != GE_KB_PAUSE \
    || GLFW_KEY_F1 != GE_KB_F1 \
    || GLFW_KEY_F2 != GE_KB_F2 \
    || GLFW_KEY_F3 != GE_KB_F3 \
    || GLFW_KEY_F4 != GE_KB_F4 \
    || GLFW_KEY_F5 != GE_KB_F5 \
    || GLFW_KEY_F6 != GE_KB_F6 \
    || GLFW_KEY_F7 != GE_KB_F7 \
    || GLFW_KEY_F8 != GE_KB_F8 \
    || GLFW_KEY_F9 != GE_KB_F9 \
    || GLFW_KEY_F10 != GE_KB_F10 \
    || GLFW_KEY_F11 != GE_KB_F11 \
    || GLFW_KEY_F12 != GE_KB_F12 \
    || GLFW_KEY_F13 != GE_KB_F13 \
    || GLFW_KEY_F14 != GE_KB_F14 \
    || GLFW_KEY_F15 != GE_KB_F15 \
    || GLFW_KEY_F16 != GE_KB_F16 \
    || GLFW_KEY_F17 != GE_KB_F17 \
    || GLFW_KEY_F18 != GE_KB_F18 \
    || GLFW_KEY_F19 != GE_KB_F19 \
    || GLFW_KEY_F20 != GE_KB_F20 \
    || GLFW_KEY_F21 != GE_KB_F21 \
    || GLFW_KEY_F22 != GE_KB_F22 \
    || GLFW_KEY_F23 != GE_KB_F23 \
    || GLFW_KEY_F24 != GE_KB_F24 \
    || GLFW_KEY_F25 != GE_KB_F25 \
    || GLFW_KEY_KP_0 != GE_KB_KP_0 \
    || GLFW_KEY_KP_1 != GE_KB_KP_1 \
    || GLFW_KEY_KP_2 != GE_KB_KP_2 \
    || GLFW_KEY_KP_3 != GE_KB_KP_3 \
    || GLFW_KEY_KP_4 != GE_KB_KP_4 \
    || GLFW_KEY_KP_5 != GE_KB_KP_5 \
    || GLFW_KEY_KP_6 != GE_KB_KP_6 \
    || GLFW_KEY_KP_7 != GE_KB_KP_7 \
    || GLFW_KEY_KP_8 != GE_KB_KP_8 \
    || GLFW_KEY_KP_9 != GE_KB_KP_9 \
    || GLFW_KEY_KP_DECIMAL != GE_KB_KP_DECIMAL \
    || GLFW_KEY_KP_DIVIDE != GE_KB_KP_DIVIDE \
    || GLFW_KEY_KP_MULTIPLY != GE_KB_KP_MULTIPLY \
    || GLFW_KEY_KP_SUBTRACT != GE_KB_KP_SUBTRACT \
    || GLFW_KEY_KP_ADD != GE_KB_KP_ADD \
    || GLFW_KEY_KP_ENTER != GE_KB_KP_ENTER \
    || GLFW_KEY_KP_EQUAL != GE_KB_KP_EQUAL \
    || GLFW_KEY_LEFT_SHIFT != GE_KB_LEFT_SHIFT \
    || GLFW_KEY_LEFT_CONTROL != GE_KB_LEFT_CONTROL \
    || GLFW_KEY_LEFT_ALT != GE_KB_LEFT_ALT \
    || GLFW_KEY_LEFT_SUPER != GE_KB_LEFT_SUPER \
    || GLFW_KEY_RIGHT_SHIFT != GE_KB_RIGHT_SHIFT \
    || GLFW_KEY_RIGHT_CONTROL != GE_KB_RIGHT_CONTROL \
    || GLFW_KEY_RIGHT_ALT != GE_KB_RIGHT_ALT \
    || GLFW_KEY_RIGHT_SUPER != GE_KB_RIGHT_SUPER \
    || GLFW_KEY_MENU != GE_KB_MENU \
    || GLFW_KEY_LAST != GE_KB_LAST

  #error GE KB VALUES NOT SET CORRECTLY

#endif

#if    GLFW_MOUSE_BUTTON_1 != GE_MOUSE_1 \
    || GLFW_MOUSE_BUTTON_2 != GE_MOUSE_2 \
    || GLFW_MOUSE_BUTTON_3 != GE_MOUSE_3 \
    || GLFW_MOUSE_BUTTON_4 != GE_MOUSE_4 \
    || GLFW_MOUSE_BUTTON_5 != GE_MOUSE_5 \
    || GLFW_MOUSE_BUTTON_6 != GE_MOUSE_6 \
    || GLFW_MOUSE_BUTTON_7 != GE_MOUSE_7 \
    || GLFW_MOUSE_BUTTON_8 != GE_MOUSE_8 \
    || GLFW_MOUSE_BUTTON_LAST != GE_MOUSE_LAST \
    || GLFW_MOUSE_BUTTON_LEFT != GE_MOUSE_LEFT \
    || GLFW_MOUSE_BUTTON_RIGHT != GE_MOUSE_RIGHT \
    || GLFW_MOUSE_BUTTON_MIDDLE != GE_MOUSE_MIDDLE

  #error GE MOUSE VALUES NOT SET CORRECTLY

#endif

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

bool geKey_Down(geGame* game, int key) {
  return glfwGetKey(game->window->_window_ID, key) == GLFW_PRESS;
}
bool geKey_Up(geGame* game, int key) {
  return glfwGetKey(game->window->_window_ID, key) == GLFW_RELEASE;
}
bool geMouse_Down(geGame* game, int button) {
  return glfwGetMouseButton(game->window->_window_ID, button) == GLFW_PRESS;
}
bool geMouse_Up(geGame* game, int button) {
  return glfwGetMouseButton(game->window->_window_ID, button) == GLFW_RELEASE;
}
