//TODO: find init valeus for grCreate_Texture_NULL

#ifndef GR_TEXTURE_H
#define GR_TEXTURE_H

#include <stdint.h>
#include <stdarg.h>

#include <Game_Engine/Graphics/Formats/grColours.h>

#include "grImage.h"

typedef
struct grTexture {
  uint32_t _X_pixels;
  uint32_t _Y_pixels;
  uint32_t _n_channels;

  grColour _colour_format;

  unsigned int _OpenGL_ID;
} grTexture;

// ==========================
// Initializaiton/Termination
// ==========================

// Imports image from file path.  Stored in GPU RAM.
// Imported as per grCreate_Image.
grTexture grTexture_init(const char* path);
// Uploads image to GPU RAM
grTexture grTexture_From_Image_init(grImage* image);
// Uploads image to GPU RAM with dimensions (X_pixels, Y_pixels) with values //...!!!???
grTexture grTexture_Empty_init(int X_pixels, int Y_pixels);

// Frees all texture data (from RAM/GPU).
void grTexture_term(grTexture* texture);

#endif
