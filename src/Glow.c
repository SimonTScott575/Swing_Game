#include <Glow.h>

int g_glow_screen_x = 1200;
int g_glow_screen_y = 800;

float Screen_X1 = -1;
float Screen_Y1 = -1;
float Screen_X2 =  1;
float Screen_Y2 =  1;

grShader Glow_Shader;
static grTexture Glow_Texture;
static grScreen Glow_Screen;

void Init_Glow_PP(int x, int y) {

  g_glow_screen_x = x;
  g_glow_screen_y = y;

  Glow_Texture = grTexture_Empty_init(g_glow_screen_x,g_glow_screen_y);

  Glow_Shader = grShader_init("../Resources/Shaders/glow_shader_vert.glsl",
                              "../Resources/Shaders/glow_shader_frag.glsl");
  grSet_Texture_by_name("grTexture", &Glow_Texture, &Glow_Shader);

  Glow_Screen = grScreen_init(&Glow_Texture);

}

void Terminate_Glow_PP() {

  grShader_term(&Glow_Shader);
  grTexture_term(&Glow_Texture);
  grScreen_term(&Glow_Screen);

}

void Glow_PP(grScreen* screen) {

  if (   g_glow_screen_x != geGet_Active_Game()->window->_X_pixels
      || g_glow_screen_y != geGet_Active_Game()->window->_Y_pixels) {

    g_glow_screen_x = geGet_Active_Game()->window->_X_pixels;
    g_glow_screen_y = geGet_Active_Game()->window->_Y_pixels;

    grTexture_term(&Glow_Texture);
    grScreen_term(&Glow_Screen);

    Glow_Texture = grTexture_Empty_init(g_glow_screen_x,g_glow_screen_y);

    grSet_Texture_by_name("grTexture", &Glow_Texture, &Glow_Shader);

    Glow_Screen = grScreen_init(&Glow_Texture);

  }

  grBlit(screen, &Glow_Screen, NULL);
  grBlit(&Glow_Screen, screen, &Glow_Shader);

}
