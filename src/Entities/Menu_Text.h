#ifndef MENU_TEXT_H
#define MENU_TEXT_H

#define GE_INCLUDE_GLFW
#include <Game_Engine/Game_Engine.h>

typedef struct Menu_Text Menu_Text;

struct Menu_Text {

  geEntity* _super;

  mFrame2D* frame;

  grFont* font;
  grText* text;
  grShader* shader;

  grText_Renderer* text_r;

  grTexture* textures[128];

};

Menu_Text* Create_Menu_Text(const char* text, const char* font_path, float rel_X, float rel_Y, float abs_X, float abs_Y, float scale);
Menu_Text* Create_Menu_Text_With_Resolution(const char* contents, const char* font_path, float rel_X, float rel_Y, float abs_X, float abs_Y, float scale, int res) ;

void Destroy_Menu_Text_Sub_Entity(geEntity* entity);

#endif
