#ifndef GR_SPRITE_H
#define GR_SPRITE_H

#include <Game_Engine/ECS/geComponent.h>

#include <Game_Engine/Graphics/grTexture.h>
#include <Game_Engine/Graphics/grModel.h>
#include <Game_Engine/Graphics/grShader.h>

typedef
struct grSprite {

  grTexture* _texture;
  grModel* _model;
  grShader* _shader;

} grSprite;

grSprite* grCreate_Sprite(char* path, float width,  float height);
void grDestroy_Sprite(grSprite* sprite);

#endif
