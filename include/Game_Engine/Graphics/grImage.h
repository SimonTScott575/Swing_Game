#ifndef GR_IMAGE_H
#define GR_IMAGE_H

#include <stdint.h>
#include <stdbool.h>

#include <Game_Engine/Graphics/Formats/grColours.h>

typedef
struct grImage {

  void* _data; // Image data
  bool _is_ext;

  int _width;
  int _height;
  int _n_channels;

  grColour _colour_format;

} grImage;

// Imports image at file path.  Stored in CPU RAM.
// ALWAYS stored with 4 channels - RGBA //? default value if mismatch ?
// Supported file types: JPEG, PNG - see include/Game_ENgine/stbi_image.h for more
grImage grImage_init(const char* path);

//
grImage grImage_Data_init(int32_t width,
                          int32_t height,
                          int32_t n_channels,
                          grColour colour,
                          void* data);

// Frees all image data.
// MUST NOT be called if grImage not created with init_grImage_Data
void grImage_term(grImage* image);

#endif
