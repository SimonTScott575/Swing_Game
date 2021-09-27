#ifndef GE_UI_RENDERER_H
#define GE_UI_RENDERER_H

#include <Game_Engine/Graphics/grRenderer.h>
#include <Game_Engine/Graphics/Defaults/grCamera.h>
#include "geUI_Element.h"

typedef struct geUI_Renderer geUI_Renderer;

struct geUI_Renderer {

  grRenderer* _super;

  geUI_Element* uie;

  mFrame2D* frame;

};

geUI_Renderer* grCreate_UI_Renderer(geUI_Element* uie, grModel* model, grShader* shader);

//

void geRender_UI_Renderer(grRenderer* renderer, grCamera2D* camera);

#endif
