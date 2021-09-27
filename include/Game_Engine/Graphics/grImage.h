#ifndef GR_IMAGE_H
#define GR_IMAGE_H

#include <stdint.h>

#include <Game_Engine/Graphics/Formats/grColours.h>

typedef struct grImage grImage;

struct grImage {

  void* _data;

  int32_t _width; //? uint ?
  int32_t _height; //? uint ?
  int32_t _n_channels;

  grColour _colour_format;

};

grImage* grCreate_Image(const char* path);
void grDestroy_Image(grImage* image);

grImage init_grImage_Data(int32_t width,
                          int32_t height,
                          int32_t n_channels,
                          grColour _colour_format,
                          void* data);

#endif
