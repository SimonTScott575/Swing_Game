#include <Glow.h>

float Screen_X1 = -1;
float Screen_Y1 = -1;
float Screen_X2 =  1;
float Screen_Y2 =  1;

grShader* Glow_Shader = NULL;
grTexture* Glow_Texture = NULL;
grScreen* Glow_Screen = NULL;

void Init_Glow_PP() {

  Glow_Texture = grCreate_Texture_NULL(1200,1200);

  Glow_Shader = grCreate_Shader("../Resources/Shaders/glow_shader_vert.glsl",
                                "../Resources/Shaders/glow_shader_frag.glsl");
  grSet_Texture_by_name("grTexture", Glow_Texture, Glow_Shader);

  Glow_Screen = grCreate_Screen(Glow_Texture);

}

void Glow_PP(grScreen* screen) {

  grBlit(screen, Glow_Screen, NULL);
  grBlit(Glow_Screen, screen, Glow_Shader);

}
