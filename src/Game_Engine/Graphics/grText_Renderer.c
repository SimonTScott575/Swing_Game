#include <Game_Engine/Graphics/grText_Renderer.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <Game_Engine/Graphics/grScreen.h>

static void grDestroy_Text_Sub_Renderer(grRenderer* renderer);

// ======
// global
// ======

static grModel* gr_text_model;

void grInit_Text_Renderer() {

  gr_text_model = grCreate_Model_From_Mesh(grRect2D_Mesh);

}

// ===

grText* grCreate_Text(const char* contents, grFont* font) {

  grText* text = malloc(sizeof(grText));
  *text = (grText){
    ._contents = strdup(contents),
    .font = font,
    .alignment = GR_ALIGN_LEFT
  };

  return text;

}
void grDestroy_Text(grText* text) {

  free(text->_contents);

  free(text);

}

grText_Renderer* grCreate_Text_Renderer_2D(grText* text, mFrame2D* frame, grShader* shader) { //!!! SCOPE OF TEXT ??? typically won't be malloces ...

  grText_Renderer* text_r = malloc(sizeof(grText_Renderer));

  text_r->text = text;

  text_r->frame = frame;
  text_r->rel_X = 0;
  text_r->rel_Y = 0;

  text_r->_renderer_frame = mFrame2D_I;

  text_r->_super = grCreate_Renderer_2D(&text_r->_renderer_frame, gr_text_model, shader);
  text_r->_super->render_fn = grRender_Text_Renderer;
  grSet_Sub_Renderer(text_r, grDestroy_Text_Sub_Renderer, text_r->_super);

  return text_r;

}
grFont* grCreate_Font(const char* path, int32_t size) {

  FT_Library ft; //? init for lifetime of game_engine ?
  if (FT_Init_FreeType(&ft)) { goto ft_fail; }

  grFont* font = malloc(sizeof(grFont));
  if (font == NULL) { goto font_fail; }
  font->_characters = calloc(128,sizeof(grCharacter));
  if (font->_characters == NULL) { goto characters_fail; }
  font->_characters_count = 128;

  FT_Face face;
  bool face_loaded;
  if ( face_loaded = !FT_New_Face(ft, path, 0, &face) ) {

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, size);

    //!!! CHECK HOW TO USE CORRECTLY IN CONJUCTION WITH REST OF GAME ENGINE!
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //? undo this for future textures ?

    for (unsigned char c = 0; c < 128; c++) {

      if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          printf("ERROR : Failed to load Glyph"); //!!! NEED to handle this
          continue;
      }

      grImage image = init_grImage_Data(face->glyph->bitmap.width, face->glyph->bitmap.rows, 1, grColours.R, face->glyph->bitmap.buffer);

      font->_characters[c] = (grCharacter){
        ._texture = grCreate_Texture_From_Image(&image),
        ._width = face->glyph->bitmap.width,
        ._height = face->glyph->bitmap.rows,
        ._bearing_X = face->glyph->bitmap_left,
        ._bearing_Y = face->glyph->bitmap_top,
        ._advance = face->glyph->advance.x
      };

    }

  } else {
    goto face_fail;
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  goto no_fail;

  face_fail :
    free(font->_characters);
  characters_fail :
    free(font);
  font_fail :
    FT_Done_FreeType(ft);
  ft_fail :
    //? printf("\nERROR : Failed to init FreeType.\n");
  return NULL;

  no_fail :

  return font;

}

static void grDestroy_Text_Sub_Renderer(grRenderer* renderer) {

  grText_Renderer* text_r = renderer->_sub;

  free(text_r);

}
void grDestroy_Font(grFont* font) {

  for (uint32_t i = 0; i < font->_characters_count; i++) {
    grDestroy_Texture(font->_characters[i]._texture);
  }
  free(font->_characters);

  free(font);

}

void grRender_Text_Renderer(grRenderer* renderer, grCamera2D* camera) {

  grText_Renderer* text_r = renderer->_sub;
  mFrame2D* frame = text_r->frame;
  mFrame2D* renderer_f = renderer->frame;

  grScreen* screen = grGet_Active_Screen();
  grCharacter* characters = text_r->text->font->_characters;

  float alignment_length = 0;
  if (text_r->text->alignment != GR_ALIGN_LEFT) {
    for (const char* c = text_r->text->_contents; *c != '\0'; c++) {
      alignment_length += characters[*c]._advance/64.0; // * ((mFrame2D*)text_r->_super->frame)->scale.i[0];
    }

    alignment_length *= (text_r->text->alignment == GR_ALIGN_RIGHT ? -1 : -0.5);
  }
  float xpos = alignment_length;// ((mFrame2D*)text_r->_super->frame)->position.i[0];
  float ypos = 0;// ((mFrame2D*)text_r->_super->frame)->position.i[1];

  float ar = grGet_Active_Screen()->_Y_pixels/(float)grGet_Active_Screen()->_X_pixels;
  float X_length = camera->_X_length;
  float Y_length = ar*camera->_X_length/2;

  for (char* c = text_r->text->_contents; *c != '\0'; c++) {

    grCharacter ch = characters[*c];

    grSet_Texture_by_name("grTexture", ch._texture, renderer->shader);

    // set model size
    float width = ch._width;// *frame->scale.i[0];
    float height = ch._height;// *frame->scale.i[1];
    ypos = ch._bearing_Y - height;
    float vertices[4][4] = {
      {
        ( xpos          + ch._bearing_X )/1000.0, //? (float)screen->_X_pixels,//*X_length,
        ( ypos                         )/1000.0, //? /(float)screen->_Y_pixels,//*Y_length,
         0,0
      },
      {
        ( xpos + width  + ch._bearing_X )/1000.0, //? (float)screen->_X_pixels,//*X_length,
        ( ypos + height                )/1000.0, //? /(float)screen->_Y_pixels,//*Y_length,
         1,1
      },
      {
        ( xpos          + ch._bearing_X )/1000.0, //? (float)screen->_X_pixels,//*X_length,
        ( ypos + height                )/1000.0, //? /(float)screen->_Y_pixels,//*Y_length,
         0,1
      },
      {
        ( xpos + width  + ch._bearing_X )/1000.0, //? (float)screen->_X_pixels,//*X_length,
        ( ypos                         )/1000.0, //? /(float)screen->_Y_pixels,//*Y_length,
         1,0
      }
    };
    glBindBuffer(GL_ARRAY_BUFFER, gr_text_model->_OpenGL_IDs.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // set renderer frame
    renderer_f->position = mAdd_V2f(
      (mVector2f){{text_r->rel_X*camera->_X_length/2,text_r->rel_Y*Y_length}},
      frame->position
    );
    renderer_f->rotation = frame->rotation;
    renderer_f->scale = frame->scale;

    // set MVP and render
    grRender_2D(renderer, camera);

    // advance
    xpos += ch._advance/64.0;// * ((mFrame2D*)text_r->_super->frame)->scale.i[0];

  }

}

//!!! not the best for constantly setting text ...
void grSet_Text_Contents(char* s, grText* text) {

  uint64_t length = strlen(s);

  text->_contents = realloc(text->_contents, length+1);
  memcpy(text->_contents, s, length+1);

}
