#ifndef GR_SPRITE_H
#define GR_SPRITE_H

#include <Game_Engine/ECS/geComponent.h>

#include <Game_Engine/Graphics/Graphics.h>

typedef struct grSprite grSprite;

struct grSprite {

  geComponent* _super;

  grTexture* _texture;
  grModel* _model;
  grShader* _shader;

};

grSprite* grCreate_Sprite(char* path, float width,  float height);

// void grDestroy_Sprite(grSprite* sprite);
void grDestroy_Sprite_Sub_Component(geComponent* component);

#endif
