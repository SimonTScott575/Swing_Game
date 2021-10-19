#ifndef GE_INPUT_H
#define GE_INPUT_H

#include <stdbool.h>

#include <Game_Engine/geInput_States.h>
#include <Game_Engine/geGame.h>

// kb_key's
#define GE_KB_UNKNOWN   -1
#define GE_KB_SPACE   32
#define GE_KB_APOSTROPHE   39 /* ' */
#define GE_KB_COMMA   44 /* , */
#define GE_KB_MINUS   45 /* - */
#define GE_KB_PERIOD   46 /* . */
#define GE_KB_SLASH   47 /* / */
#define GE_KB_0   48
#define GE_KB_1   49
#define GE_KB_2   50
#define GE_KB_3   51
#define GE_KB_4   52
#define GE_KB_5   53
#define GE_KB_6   54
#define GE_KB_7   55
#define GE_KB_8   56
#define GE_KB_9   57
#define GE_KB_SEMICOLON   59 /* ; */
#define GE_KB_EQUAL   61 /* = */
#define GE_KB_A   65
#define GE_KB_B   66
#define GE_KB_C   67
#define GE_KB_D   68
#define GE_KB_E   69
#define GE_KB_F   70
#define GE_KB_G   71
#define GE_KB_H   72
#define GE_KB_I   73
#define GE_KB_J   74
#define GE_KB_K   75
#define GE_KB_L   76
#define GE_KB_M   77
#define GE_KB_N   78
#define GE_KB_O   79
#define GE_KB_P   80
#define GE_KB_Q   81
#define GE_KB_R   82
#define GE_KB_S   83
#define GE_KB_T   84
#define GE_KB_U   85
#define GE_KB_V   86
#define GE_KB_W   87
#define GE_KB_X   88
#define GE_KB_Y   89
#define GE_KB_Z   90
#define GE_KB_LEFT_BRACKET   91 /* [ */
#define GE_KB_BACKSLASH   92 /* \ */
#define GE_KB_RIGHT_BRACKET   93 /* ] */
#define GE_KB_GRAVE_ACCENT   96 /* ` */
#define GE_KB_WORLD_1   161 /* non-US #1 */
#define GE_KB_WORLD_2   162 /* non-US #2 */
#define GE_KB_ESCAPE   256
#define GE_KB_ENTER   257
#define GE_KB_TAB   258
#define GE_KB_BACKSPACE   259
#define GE_KB_INSERT   260
#define GE_KB_DELETE   261
#define GE_KB_RIGHT   262
#define GE_KB_LEFT   263
#define GE_KB_DOWN   264
#define GE_KB_UP   265
#define GE_KB_PAGE_UP   266
#define GE_KB_PAGE_DOWN   267
#define GE_KB_HOME   268
#define GE_KB_END   269
#define GE_KB_CAPS_LOCK   280
#define GE_KB_SCROLL_LOCK   281
#define GE_KB_NUM_LOCK   282
#define GE_KB_PRINT_SCREEN   283
#define GE_KB_PAUSE   284
#define GE_KB_F1   290
#define GE_KB_F2   291
#define GE_KB_F3   292
#define GE_KB_F4   293
#define GE_KB_F5   294
#define GE_KB_F6   295
#define GE_KB_F7   296
#define GE_KB_F8   297
#define GE_KB_F9   298
#define GE_KB_F10   299
#define GE_KB_F11   300
#define GE_KB_F12   301
#define GE_KB_F13   302
#define GE_KB_F14   303
#define GE_KB_F15   304
#define GE_KB_F16   305
#define GE_KB_F17   306
#define GE_KB_F18   307
#define GE_KB_F19   308
#define GE_KB_F20   309
#define GE_KB_F21   310
#define GE_KB_F22   311
#define GE_KB_F23   312
#define GE_KB_F24   313
#define GE_KB_F25   314
#define GE_KB_KP_0   320
#define GE_KB_KP_1   321
#define GE_KB_KP_2   322
#define GE_KB_KP_3   323
#define GE_KB_KP_4   324
#define GE_KB_KP_5   325
#define GE_KB_KP_6   326
#define GE_KB_KP_7   327
#define GE_KB_KP_8   328
#define GE_KB_KP_9   329
#define GE_KB_KP_DECIMAL   330
#define GE_KB_KP_DIVIDE   331
#define GE_KB_KP_MULTIPLY   332
#define GE_KB_KP_SUBTRACT   333
#define GE_KB_KP_ADD   334
#define GE_KB_KP_ENTER   335
#define GE_KB_KP_EQUAL   336
#define GE_KB_LEFT_SHIFT   340
#define GE_KB_LEFT_CONTROL   341
#define GE_KB_LEFT_ALT   342
#define GE_KB_LEFT_SUPER   343
#define GE_KB_RIGHT_SHIFT   344
#define GE_KB_RIGHT_CONTROL   345
#define GE_KB_RIGHT_ALT   346
#define GE_KB_RIGHT_SUPER   347
#define GE_KB_MENU   348
#define GE_KB_LAST  GE_KB_MENU

// mouse_key's
#define GE_MOUSE_1   0
#define GE_MOUSE_2   1
#define GE_MOUSE_3   2
#define GE_MOUSE_4   3
#define GE_MOUSE_5   4
#define GE_MOUSE_6   5
#define GE_MOUSE_7   6
#define GE_MOUSE_8   7
#define GE_MOUSE_LAST  GE_MOUSE_8
#define GE_MOUSE_LEFT  GE_MOUSE_1
#define GE_MOUSE_RIGHT  GE_MOUSE_2
#define GE_MOUSE_MIDDLE  GE_MOUSE_3

// returns true if corresponding key was pressed down on last input poll after
// which it return false even if key is still held down, else returns false
bool geKey_Down_Stroke(geGame* game, int kb_key);
bool geKey_Up_Stroke(geGame* game, int kb_key);
bool geMouse_Button_Down_Stroke(geGame* game, int mouse_key);
bool geMouse_Button_Up_Stroke(geGame* game, int mouse_key);

// returns true if key is down on last input poll (continues to return true so
// long as pressed down), else returns false
bool geKey_Down(geGame* game, int kb_key);
bool geKey_Up(geGame* game, int kb_key);
bool geMouse_Down(geGame* game, int mouse_key);
bool geMouse_Up(geGame* game, int mouse_key);

#endif
