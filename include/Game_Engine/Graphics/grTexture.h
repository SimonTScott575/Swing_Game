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

// ====================
// Creation/Destruction
// ====================

grTexture* grCreate_Texture(const char* path);
grTexture* grCreate_Texture_From_Image(grImage* image);
grTexture* grCreate_Texture_NULL(int X_pixels, int Y_pixels);

void grDestroy_Texture(grTexture* texture);

#endif
