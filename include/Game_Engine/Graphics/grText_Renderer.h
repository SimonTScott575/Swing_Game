#ifndef GR_TEXT_H
#define GR_TEXT_H

#include <stdbool.h>

#include <Game_Engine/Graphics/grTexture.h>
#include <Game_Engine/Graphics/grRenderer.h>

#define GR_ALIGN_LEFT   0
#define GR_ALIGN_RIGHT  1
#define GR_ALIGN_CENTRE 2

typedef struct grText grText;
typedef struct grText_Renderer grText_Renderer;
typedef struct grCharacter grCharacter;
typedef struct grFont grFont;

struct grFont {
  grCharacter* _characters;
  uint32_t _characters_count;
};
struct grCharacter {
  grTexture* _texture;

  int32_t _width;
  int32_t _height;

  int32_t _bearing_X;
  int32_t _bearing_Y;

  int32_t _advance;
};

struct grText {
  char* _contents;

  grFont* font;

  int alignment;
};

struct grText_Renderer {

  grRenderer* _super;

  mFrame2D* frame;
  float rel_X;
  float rel_Y;

  grText* text;
  // //TODO: grText, there set alignment too
  // const char* text;
  // grFont* font;

  mFrame2D _renderer_frame;

};

// ======
// global
// ======

void grInit_Text_Renderer();

// ===

grText* grCreate_Text(const char* contents, grFont* font);
void grDestroy_Text(grText* text);

grFont* grCreate_Font(const char* path, int32_t size);
void grDestroy_Font(grFont* font);

grText_Renderer* grCreate_Text_Renderer_2D(grText* text, mFrame2D* frame, grShader* shader);

// ===

void grRender_Text_Renderer(grRenderer* renderer, grCamera2D* camera);

void grSet_Text_Contents(char* s, grText* text);


#endif
