#ifndef GR_IMAGE_H
#define GR_IMAGE_H

#include <stdint.h>

#include <Game_Engine/Graphics/Formats/grColours.h>

typedef struct grImage grImage;

struct grImage {

  void* _data; // Image data

  int _width;
  int _height;
  int _n_channels;

  grColour _colour_format;

};

// Imports image at file path.  Stored in CPU RAM.
// ALWAYS stored with 4 channels - RGBA //? default value if mismatch ?
// Supported file types: JPEG, PNG - see include/Game_ENgine/stbi_image.h for more
grImage* grCreate_Image(const char* path);

//
grImage init_grImage_Data(int width,
                          int height,
                          int n_channels,
                          grColour _colour_format,
                          void* data);

// Frees all image data.
// MUST NOT be called if grImage not created with init_grImage_Data
void grDestroy_Image(grImage* image);

#endif
