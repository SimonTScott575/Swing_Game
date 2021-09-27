#include <Game_Engine/Graphics/grTexture.h>

#include <stdio.h>
#include <stdarg.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

// ====================
// Creation/Destruction
// ====================

grTexture* grCreate_Texture(const char* path) {

  grImage* image = grCreate_Image(path);

  grTexture* texture = grCreate_Texture_From_Image(image);

  grDestroy_Image(image);

  return texture;

}
grTexture* grCreate_Texture_NULL(int X_pixels, int Y_pixels) {

  grImage image = init_grImage_Data(X_pixels, Y_pixels, 4, grColours.RGBA, NULL);

  grTexture* texture = grCreate_Texture_From_Image(&image);

  return texture;

}

grTexture* grCreate_Texture_From_Image(grImage* image) {

  grTexture* texture = malloc(sizeof(grTexture));
  if (texture == NULL) {
    printf("\nERROR : Unable to malloc grTexture.\n");
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
