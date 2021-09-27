//TODO: MUST check if all operates as expected (according to docs too).
//           eg, what does clearX do if X buffer bit not enabled ?

#include <Game_Engine/Graphics/grScreen.h>

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/Graphics/grModel.h>

static const uint32_t grSCREEN_COLOUR_MASK = GL_COLOR_BUFFER_BIT;
static const uint32_t grSCREEN_DEPTH_MASK  = GL_DEPTH_BUFFER_BIT;
static const uint32_t grSCREEN_STENCIL_MASK = GL_STENCIL_BUFFER_BIT;

static grScreen grFIRST_SCREEN = {
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

  ._OpenGL_ENABLED_FLAG = grSCREEN_COLOUR_MASK, //TODO: change to grSCREEN_COLOUR_MASK, if it compiles
  ._OpenGL_ID = 0
};
static grScreen grSECOND_SCREEN = {
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

  ._OpenGL_ENABLED_FLAG = grSCREEN_COLOUR_MASK, //TODO: change to grSCREEN_COLOUR_MASK, if it compiles
  ._OpenGL_ID = 0
};

// grScreen* grBack_Screen = &grFIRST_SCREEN; //? don't actually have a default screen ?
// grScreen* grFront_Screen = &grSECOND_SCREEN; //? don't actually have a default screen ?
// grScreen* grActive_Screen = NULL;
static grScreen* grActive_Screen;

// static grShader* grDEFAULT_SCREEN_SHADER;
static grModel* grDEFAULT_SCREEN_MODEL;

struct grTests grTests = {
  .ALWAYS = GL_ALWAYS,
  .NEVER  = GL_NEVER,
  .E      = GL_EQUAL,
  .NE     = GL_NOTEQUAL,
  .LT     = GL_LESS,
  .GT     = GL_GREATER,
  .LTE    = GL_LEQUAL,
  .GTE    = GL_GEQUAL
};

struct grActions grActions = {
  .KEEP     = GL_KEEP,
  .ZERO     = GL_ZERO,
  .REPLACE  = GL_REPLACE,
  .INC      = GL_INCR,
  .INC_WRAP = GL_INCR_WRAP,
  .DEC      = GL_DECR,
  .DEC_WRAP = GL_DECR_WRAP,
  .INVERT   = GL_INVERT
};

// ======
// Module
// ======

void grInit_Screen() {

  // grTests.ALWAYS = GL_ALWAYS;
  // grTests.NEVER  = GL_NEVER;
  // grTests.E      = GL_EQUAL;
  // grTests.NE     = GL_NOTEQUAL;
  // grTests.LT     = GL_LESS;
  // grTests.GT     = GL_GREATER;
  // grTests.LTE    = GL_LEQUAL;
  // grTests.GTE    = GL_GEQUAL;

  // grActions.KEEP     = GL_KEEP;
  // grActions.ZERO     = GL_ZERO;
  // grActions.REPLACE  = GL_REPLACE;
  // grActions.INC      = GL_INCR;
  // grActions.INC_WRAP = GL_INCR_WRAP;
  // grActions.DEC      = GL_DECR;
  // grActions.DEC_WRAP = GL_DECR_WRAP;
  // grActions.INVERT   = GL_INVERT;

  // grFront_Screen->_colour_texture = NULL;
  // grFront_Screen->_stencil_test = grTests.ALWAYS;
  // grFront_Screen->_sFAIL       = grActions.KEEP;
  // grFront_Screen->_sPASS_dFAIL = grActions.KEEP;
  // grFront_Screen->_sPASS_dPASS = grActions.KEEP;
  // grFront_Screen->_X_pixels = X_pixels;
  // grFront_Screen->_Y_pixels = Y_pixels;
  // grBack_Screen->_colour_texture = NULL;
  // grBack_Screen->_stencil_test = grTests.ALWAYS;
  // grBack_Screen->_sFAIL       = grActions.KEEP;
  // grBack_Screen->_sPASS_dFAIL = grActions.KEEP;
  // grBack_Screen->_sPASS_dPASS = grActions.KEEP;
  // grBack_Screen->_X_pixels = X_pixels;
  // grBack_Screen->_Y_pixels = Y_pixels;
  // grSet_Active_Screen(grBack_Screen);

  float mesh_data[] = { -1, -1,   0, 0,
                         1,  1,   1, 1,
                        -1,  1,   0, 1,
                         1, -1,   1, 0  };
  int32_t mesh_indices[] = { 0,1,2, 0,3,1 };
  grType mesh_types[] = { grTypes._float, grTypes._float };
  uint32_t mesh_counts[] = { 2, 2 };
  size_t mesh_offsets[] = { 0, 2*sizeof(float) };
  grMesh mesh = {
    .vertices_data = mesh_data,
    .indices = mesh_indices,
    .types = mesh_types,
    .counts = mesh_counts,
    .vertices_data_length = 4,
    .indices_length = 6,
    .types_length = 2,

    .offsets = mesh_offsets,
    .size_of_vertex = 4*sizeof(float)
  };

  grDEFAULT_SCREEN_MODEL = grCreate_Model_From_Mesh(&mesh); //! NEED destroy

}

void grSet_Active_Screen(grScreen* screen) {
  grActive_Screen = screen;

  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);

  if (screen->_OpenGL_ENABLED_FLAG & grSCREEN_DEPTH_MASK) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  if (screen->_OpenGL_ENABLED_FLAG & grSCREEN_STENCIL_MASK) {
    glEnable(GL_STENCIL_TEST);
  } else {
    glDisable(GL_STENCIL_TEST);
  }
  glColorMask(screen->_colour_mask & 1, screen->_colour_mask & 2, screen->_colour_mask & 4, screen->_colour_mask & 8);
  glDepthMask(screen->_depth_mask & 1);
  glStencilMask(screen->_stencil_mask);

  glClearColor(screen->_clear_colour[0],
               screen->_clear_colour[1],
               screen->_clear_colour[2],
               screen->_clear_colour[3]);
  glClearDepth(screen->_clear_depth);
  glClearStencil(screen->_clear_stencil);
}
grScreen* grGet_Active_Screen() {
  return grActive_Screen;
}

// ====================
// Creation/Destruction
// ====================

grScreen* grCreate_Screen(grTexture* colour_texture) {
  grScreen* screen = malloc(sizeof(grScreen));

  screen->_colour_texture = colour_texture;

  screen->_clear_colour[0] = 0;
  screen->_clear_colour[1] = 0;
  screen->_clear_colour[2] = 0;
  screen->_clear_colour[3] = 1;
  screen->_clear_depth = 1;
  screen->_clear_stencil = 0;

  screen->_X_pixels = colour_texture->_X_pixels;
  screen->_Y_pixels = colour_texture->_Y_pixels;

  screen->_colour_mask = 1 | 2 | 4 | 8;
  screen->_depth_mask = 1;
  screen->_stencil_mask = 0xFFFFFFFF;

  //... !!! other fields to set to defaults !

  screen->_OpenGL_ENABLED_FLAG = GL_COLOR_BUFFER_BIT;

  unsigned int FBO;
  glGenFramebuffers(1, &FBO);

  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_texture->_OpenGL_ID, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, grActive_Screen->_OpenGL_ID); //? need this line ?

  screen->_OpenGL_ID = FBO;

  return screen;
}

void grDestroy_Screen(grScreen* screen) {
  free(screen);
}

//TODO: grDestroy

// ===

void grSet_Screen_Texture(grTexture* texture, grScreen* screen) {

  screen->_colour_texture = texture;

  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->_OpenGL_ID, 0);

  screen->_X_pixels = texture->_X_pixels;
  screen->_Y_pixels = texture->_Y_pixels;

}

// ===================
// Enable/Disable/Mask
// ===================

// Colour/Depth/Stencil Masks
void grSet_Screen_Colour_Mask(bool red, bool green, bool blue, bool alpha, grScreen* screen) {
  screen->_colour_mask = (1*red) | (2*green) | (4*blue) | (8*alpha);

  if (grActive_Screen == screen) {
    glColorMask(red, green, blue, alpha);
  }
}
void grSet_Screen_Depth_Mask(bool writeable, grScreen* screen) {
  screen->_depth_mask = writeable;

  if (grActive_Screen == screen) {
    glDepthMask(writeable);
  }
}
void grSet_Screen_Stencil_Mask(uint32_t stencil_mask, grScreen* screen) {
  screen->_stencil_mask = stencil_mask;

  if (grActive_Screen == screen) {
    glStencilMask(stencil_mask);
  }
}

// Depth Testing
void grEnable_Screen_Depth_Test(grScreen* screen) {
  screen->_OpenGL_ENABLED_FLAG |= grSCREEN_DEPTH_MASK;

  if (screen == grActive_Screen) {
    glEnable(GL_DEPTH_TEST);
  }
}
void grDisable_Screen_Depth_Test(grScreen* screen) {
  screen->_OpenGL_ENABLED_FLAG &= ~grSCREEN_DEPTH_MASK;

  if (screen == grActive_Screen) {
    glDisable(GL_DEPTH_TEST);
  }
}

// Stencil Testing
void grEnable_Screen_Stencil_Test(grScreen* screen) {
  screen->_OpenGL_ENABLED_FLAG |= grSCREEN_STENCIL_MASK;

  if (screen == grActive_Screen) {
    glEnable(GL_STENCIL_TEST);
  }
}
void grDisable_Screen_Stencil_Test(grScreen* screen) {
  screen->_OpenGL_ENABLED_FLAG &= ~grSCREEN_STENCIL_MASK;

  if (screen == grActive_Screen) {
    glDisable(GL_STENCIL_TEST);
  }
}

// Face culling
void grEnable_Face_Culling(grScreen* screen) {
  screen->_cull_face_enabled = 1;

  if (screen == grActive_Screen) {
    glEnable(GL_CULL_FACE);
  }
}
void grDisable_Face_Culling(grScreen* screen) {
  screen->_cull_face_enabled = 0;

  if (screen == grActive_Screen) {
    glDisable(GL_CULL_FACE);
  }
}

// ===
// Add
// ===

void grAdd_Screen_Depth_Buffer(grScreen* screen) { //TODO: untested
  uint32_t d_texture;
  glGenTextures(1, &d_texture);
  glBindTexture(GL_TEXTURE_2D, d_texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screen->_X_pixels, screen->_Y_pixels, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, d_texture, 0);

  screen->_OpenGL_ENABLED_FLAG |= GL_DEPTH_BUFFER_BIT;
}

void grAdd_Screen_Depth_Stencil_Buffer(grScreen* screen) { //TODO: untested
  uint32_t ds_texture;
  glGenTextures(1, &ds_texture);
  glBindTexture(GL_TEXTURE_2D, ds_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screen->_X_pixels, screen->_Y_pixels, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ds_texture, 0);

  screen->_OpenGL_ENABLED_FLAG |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
}

// void grAdd_Screen_Buffer(int depth, int stencil, grScreen* screen) { //TODO: write better so no repetition
//   if (depth && stencil) {                                            //? grTexture*, ... so if no texture to add then give depth/stencil bools ???
//     uint32_t ds_texture;
//     glGenTextures(1, &ds_texture);
//     glBindTexture(GL_TEXTURE_2D, ds_texture);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screen->_X_pixels, screen->_Y_pixels, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
//
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ds_texture, 0);
//
//     screen->_OpenGL_ENABLED_FLAG |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
//   } else {
//     if (depth) {
//       uint32_t d_texture;
//       glGenTextures(1, &d_texture);
//       glBindTexture(GL_TEXTURE_2D, d_texture);
//
//       glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, screen->_X_pixels, screen->_Y_pixels, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
//
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//       glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, d_texture, 0);
//
//       screen->_OpenGL_ENABLED_FLAG |= GL_DEPTH_BUFFER_BIT;
//     }
//   }
// }

// =====
// Clear
// =====

void grClear_Screen(grScreen* screen) { //? enable before clear ?
  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);

  glClearColor(screen->_clear_colour[0],
               screen->_clear_colour[1],
               screen->_clear_colour[2],
               screen->_clear_colour[3]);
  glClearDepth(screen->_clear_depth);
  glClearStencil(screen->_clear_stencil);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //? what if not enabled, will it clear ?

  grSet_Active_Screen(grActive_Screen);
}
void grClear_Screen_Colour(grScreen* screen) {
  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);

  glClearColor(screen->_clear_colour[0],
               screen->_clear_colour[1],
               screen->_clear_colour[2],
               screen->_clear_colour[3]);
  glClear(GL_COLOR_BUFFER_BIT);

  grSet_Active_Screen(grActive_Screen);
}
void grClear_Screen_Depth(grScreen* screen) {
  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);

  glClearDepth(screen->_clear_depth);
  glClear(GL_DEPTH_BUFFER_BIT);

  grSet_Active_Screen(grActive_Screen);
}
void grClear_Screen_Stencil(grScreen* screen) {
  glBindFramebuffer(GL_FRAMEBUFFER, screen->_OpenGL_ID);

  glClearStencil(screen->_clear_stencil);
  glClear(GL_STENCIL_BUFFER_BIT);

  grSet_Active_Screen(grActive_Screen);
}

void grSet_Clear_Screen_Colour(float colour[4], grScreen* screen) { //! find way to specify screen //! should work when not enabled ?
  screen->_clear_colour[0] = colour[0];
  screen->_clear_colour[1] = colour[1];
  screen->_clear_colour[2] = colour[2];
  screen->_clear_colour[3] = colour[3];

  if (screen == grActive_Screen) {
    glClearColor(screen->_clear_colour[0],
                 screen->_clear_colour[1],
                 screen->_clear_colour[2],
                 screen->_clear_colour[3]);
  }
}
void grSet_Clear_Screen_Depth(double depth, grScreen* screen) {
  screen->_clear_depth = depth;

  if (screen == grActive_Screen) {
    glClearDepth(depth);
  }
}
void grSet_Clear_Screen_Stencil(int32_t stencil, grScreen* screen) {
  screen->_clear_stencil = stencil;

  if (screen == grActive_Screen) {
    glClearStencil(stencil);
  }
}

// ============
// Stencil Test
// ============

void grSet_Screen_Stencil_Test(grTest test, int32_t ref, uint32_t test_mask, grScreen* screen) {
  screen->_stencil_test = test;
  screen->_stencil_ref = ref;
  screen->_stencil_test_mask = test_mask;

  if (screen == grActive_Screen) {
    glStencilFunc(test, ref, test_mask);
  }
}

void grSet_Screen_Stencil_Action(grAction sFAIL, grAction sPASS_dFAIL, grAction sPASS_dPASS, grScreen* screen) {
  screen->_sFAIL = sFAIL;
  screen->_sPASS_dFAIL = sPASS_dFAIL;
  screen->_sPASS_dPASS = sPASS_dPASS;

  if (screen == grActive_Screen) {
    glStencilOp(sFAIL, sPASS_dFAIL, sPASS_dPASS);
  }
}

// ======
// Render
// ======

void grBlit(grScreen* screen, grScreen* target_screen, grShader* shader) {

  if ( shader != NULL && screen->_OpenGL_ID == 0 ) { //??? CHECK IF ZERO CORRECT
    printf("\nERROR : cannot blit with shader from back or front screens as source\n");
    return;
  }

  if (shader == NULL) {

    uint32_t prior_id = grGet_Active_Screen()->_OpenGL_ID;

    glBindFramebuffer(GL_READ_FRAMEBUFFER, screen->_OpenGL_ID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target_screen->_OpenGL_ID);
    glBlitFramebuffer(0,0, screen->_X_pixels, screen->_Y_pixels, //??? inclusive on endpoints ?
                      0,0, target_screen->_X_pixels, target_screen->_Y_pixels, //??? inclusive on endpoints ?
                      GL_COLOR_BUFFER_BIT, // screen->_OpenGL_ENABLED_FLAG & target_screen->_OpenGL_ENABLED_FLAG,
                      GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, prior_id); //? neccesary ?

  } else {

    grScreen* prior_current_screen = grActive_Screen;
    grSet_Active_Screen(target_screen);

    //? set shader in opengl ?
    glUseProgram(shader->_OpenGL_ID);

    uint32_t textures_length = shader->_textures_length;
    for (uint32_t i = 0; i < textures_length; i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, shader->textures[i]->_OpenGL_ID);
    }

    glBindVertexArray(grDEFAULT_SCREEN_MODEL->_OpenGL_IDs.VAO);
    glDrawElements(GL_TRIANGLES, grDEFAULT_SCREEN_MODEL->indices_length, GL_UNSIGNED_INT, 0);

    grSet_Active_Screen(prior_current_screen);

  }

}

// void grRender_Screen(grScreen* screen, GLFWwindow* window) {
//   //NOTE: would all be different if single buffered
//   //NOTE: overrides DEFAULT !!!
//
//   if (screen != grBack_Screen) {
//     grSet_Texture_by_name("grTexture", screen->_colour_texture, grDEFAULT_SCREEN_SHADER);
//     grBlit(screen, grBack_Screen, grDEFAULT_SCREEN_SHADER);
//   }
//
//   grSwap_Screens(window);
//
// }

//... grGet ... same as glGet ?
