#ifndef PORTAL_RENDERER_H
#define PORTAL_RENDERER_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Portal_Renderer {

  geComponent _super;

  grTexture grey_t;
  grTexture white_t;

  grModel model;
  grShader shader;

} Portal_Renderer;

void Portal_Renderer_ctor(Portal_Renderer* self);
void Update_Portal_Renderer(geComponent* component);
void Portal_Renderer_Sub_Component_dtor(geComponent* component);

#endif
