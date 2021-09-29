#include <Game_Engine/Graphics/grTexture.h>

#include <stdio.h>
#include <stdarg.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

#include <Game_Engine/ge_common.h>

// ====================
// Creation/Destruction
// ====================

grTexture* grCreate_Texture(const char* path) {

  grImage* image = grCreate_Image(path);
  if (image == NULL) {
    GE_DEBUG_LOG("\n%s",
                 "DEBUG : Game_Engine/Graphics/grTexture >> grCreate_Texture\n"
                 "        Failed to grCreate_Image.");
    return NULL;
  }

  grTexture* texture = grCreate_Texture_From_Image(image);

  grDestroy_Image(image);

  #ifdef GE_DEBUG_MODE
    if (texture == NULL) {
      GE_DEBUG_LOG("\n%s",
                   "DEBUG : Game_Engine/Graphics/grTexture >> grCreate_Texture\n"
                   "        Failed to grCreate_Texture_From_Image.");
    }
  #endif

  return texture;

}
grTexture* grCreate_Texture_NULL(int X_pixels, int Y_pixels) {

  grImage image = init_grImage_Data(X_pixels, Y_pixels, 4, grColours.RGBA, NULL);

  grTexture* texture = grCreate_Texture_From_Image(&image);
  #ifdef GE_DEBUG_MODE
    if (texture == NULL) {
      GE_DEBUG_LOG("\n%s",
                   "DEBUG : Game_Engine/Graphics/grTexture >> grCreate_Texture_NULL\n"
                   "        Failed to grCreate_Texture_From_Image.");
    }
  #endif

  return texture;

}

grTexture* grCreate_Texture_From_Image(grImage* image) {

  grTexture* texture = malloc(sizeof(grTexture));

  if (texture == NULL) {
    GE_DEBUG_LOG("\n%s",
                 "DEBUG : Game_Engine/Graphics/grTexture >> grCreate_Texture_From_Image\n"
                 "        Failed to malloc grTexture.");
    return NULL;
  }

  texture->_colour_format = image->_colour_format;
  texture->_X_pixels = image->_width;
  texture->_Y_pixels = image->_height;
  texture->_n_channels = image->_n_channels;

  glGenTextures(1, &texture->_OpenGL_ID);
  glBindTexture(GL_TEXTURE_2D, texture->_OpenGL_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    image->_colour_format,
    image->_width,
    image->_height,
    0,
    image->_colour_format,
    GL_UNSIGNED_BYTE,
    image->_data
  ); //!!!TODO: MUST ensure that if data == NULL then alpha 1
  glGenerateMipmap(GL_TEXTURE_2D);

  return texture;

}

// Removes texture from GPU memory and frees grTexture pointer.
void grDestroy_Texture(grTexture* texture) {
  
  glDeleteTextures(1, &texture->_OpenGL_ID);

  free(texture);
  
}
