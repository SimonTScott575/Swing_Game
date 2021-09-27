#ifndef PORTAL_RENDERER_H
#define PORTAL_RENDERER_H

#include <Game_Engine/Game_Engine.h>

typedef struct Portal_Renderer Portal_Renderer;

struct Portal_Renderer {

  geComponent* _super;

  grTexture* grey_t;
  grTexture* white_t;

  grModel* model;
  grShader* shader;

};

Portal_Renderer* Create_Portal_Renderer();
void Update_Portal_Renderer(geComponent* component);
void Destroy_Portal_Renderer_Sub_Component(geComponent* component);

#endif
