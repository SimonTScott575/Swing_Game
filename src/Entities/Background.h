#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Background {

  geEntity* _super;

  mFrame2D* frame;

  grSprite* sprite;
  grRenderer* renderer;

} Background;

Background* Create_Background(mFrame2D* camera_frame);

void Destroy_Background_Sub_Entity(geEntity* entity);

#endif
