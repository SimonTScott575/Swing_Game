#include <Glow.h>

int g_glow_screen_x = 1200;
int g_glow_screen_y = 800;

float Screen_X1 = -1;
float Screen_Y1 = -1;
float Screen_X2 =  1;
float Screen_Y2 =  1;

grShader* Glow_Shader = NULL;
grTexture* Glow_Texture = NULL;
grScreen* Glow_Screen = NULL;

void Init_Glow_PP(int x, int y) {

  g_glow_screen_x = x;
  g_glow_screen_y = y;

  Glow_Texture = grCreate_Texture_NULL(g_glow_screen_x,g_glow_screen_y);

  Glow_Shader = grCreate_Shader("../Resources/Shaders/glow_shader_vert.glsl",
                                "../Resources/Shaders/glow_shader_frag.glsl");
  grSet_Texture_by_name("grTexture", Glow_Texture, Glow_Shader);

  Glow_Screen = grCreate_Screen(Glow_Texture);

}

void Glow_PP(grScreen* screen) {

  if (   g_glow_screen_x != geGet_Active_Game()->window->_X_pixels
      || g_glow_screen_y != geGet_Active_Game()->window->_Y_pixels) {

    g_glow_screen_x = geGet_Active_Game()->window->_X_pixels;
    g_glow_screen_y = geGet_Active_Game()->window->_Y_pixels;    

    grDestroy_Texture(Glow_Texture);
    grDestroy_Screen(Glow_Screen);

    Glow_Texture = grCreate_Texture_NULL(g_glow_screen_x,g_glow_screen_y);

    grSet_Texture_by_name("grTexture", Glow_Texture, Glow_Shader);

    Glow_Screen = grCreate_Screen(Glow_Texture);

  }

  grBlit(screen, Glow_Screen, NULL);
  grBlit(Glow_Screen, screen, Glow_Shader);

}
