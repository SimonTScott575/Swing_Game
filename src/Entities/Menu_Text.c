#include "Menu_Text.h"

#include <stdbool.h>

Menu_Text* Create_Menu_Text_With_Resolution(
  const char* contents,
  const char* font_path,
  float rel_X, float rel_Y, float abs_X, float abs_Y,
  float scale,
  int res,
  geScene* scene
) {

  Menu_Text* mt = malloc(sizeof(Menu_Text));
  if (mt == NULL) { return NULL; }

  geEntity_ctor(&mt->_super);
  geSet_Sub_Entity(mt, Destroy_Menu_Text_Sub_Entity, &mt->_super);

  if (font_path == NULL) {
    font_path = "../Resources/Fonts/Fira/FiraSans-Heavy.ttf";
  }
  mt->font = grCreate_Font(font_path, res);
  mt->text = grCreate_Text(contents, mt->font);
  mt->text->alignment = GR_ALIGN_CENTRE;

  mt->frame = mFrame2D_init((mVector2f){{abs_X,abs_Y}}, 0, (mVector2f){{scale,scale}});
  mt->shader = grShader_init("../include/Game_Engine/Graphics/Shaders/grText_2D_vert.glsl",
                              "../include/Game_Engine/Graphics/Shaders/grText_2D_frag.glsl");

  mt->text_r = grCreate_Text_Renderer_2D(mt->text, &mt->frame, &mt->shader);
  mt->text_r->rel_X = rel_X;
  mt->text_r->rel_Y = rel_Y;

  geAdd_Component(&mt->text_r->_super._super, &mt->_super);

  geAdd_Entity(&mt->_super, scene);

  return mt;

}

Menu_Text* Create_Menu_Text(
  const char* contents,
  const char* font_path,
  float rel_X, float rel_Y, float abs_X, float abs_Y,
  float scale,
  geScene* scene) {

  return Create_Menu_Text_With_Resolution(contents, font_path,  rel_X, rel_Y, abs_X, abs_Y, scale, 256, scene);

}

void Destroy_Menu_Text_Sub_Entity(geEntity* entity) {

  Menu_Text* menu_text = entity->_sub;

  grDestroy_Font(menu_text->font);
  grDestroy_Text(menu_text->text);
  grShader_term(&menu_text->shader);

  free(menu_text);

}
