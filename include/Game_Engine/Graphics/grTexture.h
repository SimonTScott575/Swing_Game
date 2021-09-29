//TODO: find init valeus for grCreate_Texture_NULL

#ifndef GR_TEXTURE_H
#define GR_TEXTURE_H

#include <stdint.h>
#include <stdarg.h>

#include <Game_Engine/Graphics/Formats/grColours.h>

#include "grImage.h"

typedef struct grTexture grTexture;
struct grTexture {
  uint32_t _X_pixels;
  uint32_t _Y_pixels;
  uint32_t _n_channels;

  grColour _colour_format;

  unsigned int _OpenGL_ID;
};

// ==========================
// Initializaiton/Termination
// ==========================

// Imports image from file path.  Stored in GPU RAM.
// Imported as per grCreate_Image.
grTexture* grCreate_Texture(const char* path);
// Uploads image to GPU RAM
grTexture* grCreate_Texture_From_Image(grImage* image);
// Uploads image to GPU RAM with dimensions (X_pixels, Y_pixels) with values //...!!!???
grTexture* grCreate_Texture_NULL(int X_pixels, int Y_pixels);

// Frees all texture data (from RAM/GPU).
void grDestroy_Texture(grTexture* texture);

#endif
