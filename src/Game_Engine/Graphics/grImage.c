#include <Game_Engine/Graphics/grImage.h>

#include <Game_Engine/ge_common.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

grImage grImage_init(const char* path) {

  grImage image;

  stbi_set_flip_vertically_on_load(1);
  image._data = stbi_load(path, &image._width, &image._height, &image._n_channels, 4); //TODO: would be nice to enforce colour_format instead of just use it as descriptor
  if (image._data == NULL) {
    GE_DEBUG_LOG("\n%s",
                 "DEBUG : Game_Engine/Graphics/grImage >> grCreate_Image\n"
                 "        Failed to stbi_load image.\n");
  }

  image._colour_format = grColours.RGBA;
  image._is_ext = false;

  return image;

}

void grImage_term(grImage* image) {

  if (!image->_is_ext && image->_data != NULL) {
    stbi_image_free(image->_data);
  }

}

grImage grImage_Data_init(int32_t width,
                          int32_t height,
                          int32_t n_channels,
                          grColour colour,
                          void* data) {

  return (grImage) {
    ._width = width,
    ._height = height,
    ._n_channels = n_channels,
    ._colour_format = colour,
    ._data = data,
    ._is_ext = true
  };

}
