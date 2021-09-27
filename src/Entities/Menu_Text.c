#include "Menu_Text.h"

#include <stdbool.h>

Menu_Text* Create_Menu_Text_With_Resolution(const char* contents, float rel_X, float rel_Y, float abs_X, float abs_Y, float scale, int res) {

  geEntity* entity = geCreate_Entity();

  grFont* font = grCreate_Font("../Resources/Fonts/arial.ttf", res); // MomcakeBold-WyonA
  grText* text = grCreate_Text(contents, font);
  text->alignment = GR_ALIGN_CENTRE;

  mFrame2D* frame = new_mFrame2D((mVector2f){{abs_X,abs_Y}}, 0, (mVector2f){{scale,scale}});
  grShader* shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grText_2D_vert.glsl",
                                     "../include/Game_Engine/Graphics/Shaders/grText_2D_frag.glsl");

  grText_Renderer* text_r = grCreate_Text_Renderer_2D(text, frame, shader);
  text_r->rel_X = rel_X;
  text_r->rel_Y = rel_Y;

  geAdd_Component(frame->_super, entity);
  geAdd_Component(text_r->_super->_super, entity);

  Menu_Text* title = malloc(sizeof(Menu_Text));
  *title = (Menu_Text){
    ._super = entity,
    .frame = frame,
    .font = font,
    .text = text,
    .shader = shader,
    .text_r = text_r
  };

  geSet_Sub_Entity(title, Destroy_Menu_Text_Sub_Entity, entity);

  return title;

}

Menu_Text* Create_Menu_Text(const char* contents, float rel_X, float rel_Y, float abs_X, float abs_Y, float scale) {

  return Create_Menu_Text_With_Resolution(contents, rel_X, rel_Y, abs_X, abs_Y, scale, 256);

}

void Destroy_Menu_Text_Sub_Entity(geEntity* entity) {

  Menu_Text* menu_text = entity->_sub;

  grDestroy_Font(menu_text->font);
  grDestroy_Text(menu_text->text);
  grDestroy_Shader(menu_text->shader);

  free(menu_text);

}
