#ifndef GR_TEXT_H
#define GR_TEXT_H

#include <stdbool.h>

#include <Game_Engine/Graphics/grTexture.h>
#include <Game_Engine/Graphics/grRenderer.h>

#define GR_ALIGN_LEFT   0
#define GR_ALIGN_RIGHT  1
#define GR_ALIGN_CENTRE 2

typedef
struct grCharacter {
  grTexture _texture;

  int32_t _width;
  int32_t _height;

  int32_t _bearing_X;
  int32_t _bearing_Y;

  int32_t _advance;
} grCharacter;

typedef
struct grFont {
  grCharacter* _characters;
  uint32_t _characters_count;
} grFont;

typedef
struct grText {
  char* _contents;

  grFont* font;

  int alignment;
} grText;

typedef
struct grText_Renderer {

  grRenderer _super;

  mFrame2D* frame;
  float rel_X;
  float rel_Y;

  grText* text;

  mFrame2D _renderer_frame;

} grText_Renderer;

// ======
// global
// ======

void grInit_Text_Renderer();

void grTerminate_Text_Renderer(); //TODO: !!! MUST incorporate into engine

// ===

grText* grCreate_Text(const char* contents, grFont* font);
void grDestroy_Text(grText* text);

grFont* grCreate_Font(const char* path, int32_t size);
void grDestroy_Font(grFont* font);

grText_Renderer* grCreate_Text_Renderer_2D(grText* text, mFrame2D* frame, grShader* shader);
void grDestroy_Text_Sub_Renderer(grRenderer* renderer);

// ===

void grRender_Text_Renderer(grRenderer* renderer, grCamera2D* camera);

void grSet_Text_Contents(char* s, grText* text);


#endif
