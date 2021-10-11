#ifndef GR_SCREEN_H
#define GR_SCREEN_H

#include <stdint.h>
#include <stdbool.h>

#include "grShader.h"
#include "grTexture.h"

typedef struct grScreen grScreen;
typedef uint32_t grTest;
typedef uint32_t grAction;

struct grScreen { //TODO: should store depth/stencil buffers too
  grTexture* _colour_texture;

  float _clear_colour[4];
  double _clear_depth;
  int32_t _clear_stencil;

  uint32_t _colour_mask;
  uint32_t _depth_mask;
  uint32_t _stencil_mask;

  grTest _stencil_test;
  int32_t _stencil_ref;
  uint32_t _stencil_test_mask;
  uint32_t _sFAIL;
  uint32_t _sPASS_dFAIL;
  uint32_t _sPASS_dPASS;

  uint32_t _cull_face_enabled;

  int32_t _X_pixels;
  int32_t _Y_pixels;

  uint32_t _OpenGL_ENABLED_FLAG;
  uint32_t _OpenGL_ID;
};

struct grTests {
  grTest ALWAYS;
  grTest NEVER;
  grTest E;
  grTest NE;
  grTest LT;
  grTest GT;
  grTest LTE;
  grTest GTE;
};

struct grActions {
  grAction KEEP;
  grAction ZERO;
  grAction REPLACE;
  grAction INC;
  grAction INC_WRAP;
  grAction DEC;
  grAction DEC_WRAP;
  grAction INVERT;
};

// extern grScreen* const grDEFAULT_SCREEN;
// extern grScreen* grFront_Screen;
// extern grScreen* grBack_Screen;
// extern grScreen* grCURRENT_SCREEN;

extern struct grTests grTests;
extern struct grActions grActions;

// ======
// Module
// ======

void grInit_Screen();

// void grSwap_Screens(GLFWwindow* window);
void grSet_Active_Screen(grScreen* screen);
grScreen* grGet_Active_Screen();

// ====================
// Creation/Destruction
// ====================

grScreen* grCreate_Screen(grTexture* colour_texture);
void grDestroy_Screen(grScreen* screen);

// ===

void grSet_Screen_Texture(grTexture* texure, grScreen* screen);

// ===================
// Enable/Disable/Mask
// ===================

// Colour/Depth/Stencil Mask
void grSet_Screen_Colour_Mask(bool red, bool green, bool blue, bool alpha, grScreen* screen);
void grSet_Screen_Depth_Mask(bool writeable, grScreen* screen);
void grSet_Screen_Stencil_Mask(uint32_t stencil_mask, grScreen* screen);

// Depth Testing
void grEnable_Screen_Depth_Test(grScreen* screen);
void grDisable_Screen_Depth_Test(grScreen* screen);

// Stencil Testing
void grEnable_Screen_Stencil_Test(grScreen* screen);
void grDisable_Screen_Stencil_Test(grScreen* screen);

// Face Culling
void grEnable_Face_Culling(grScreen* screen);
void grDisable_Face_Culling(grScreen* screen);

// ===
// Add
// ===

void grAdd_Screen_Depth_Buffer(grScreen* screen);
void grAdd_Screen_Depth_Stencil_Buffer(grScreen* screen);

// void grAdd_Screen_Buffer(int depth, int stencil, grScreen* screen);

// =====
// Clear
// =====

void grClear_Screen(grScreen* screen);
void grClear_Screen_Colour(grScreen* screen);
void grClear_Screen_Depth(grScreen* screen);
void grClear_Screen_Stencil(grScreen* screen);

void grSet_Clear_Screen_Colour(float colour[4], grScreen* screen);
void grSet_Clear_Screen_Depth(double depth, grScreen* screen);
void grSet_Clear_Screen_Stencil(int32_t stencil, grScreen* screen);

// ============
// Stencil Test
// ============

void grSet_Screen_Stencil_Test(grTest test, int32_t ref, uint32_t test_mask, grScreen* screen);
void grSet_Screen_Stencil_Action(grAction s_fail, grAction s_pass_d_fail, grAction s_pass_d_pass, grScreen* screen);

// ======
// Render
// ======

void grBlit(grScreen* screen, grScreen* target_screen, grShader* shader);

// void grRender_Screen(grScreen* screen, GLFWwindow* window); //? overrides default ?

#endif
