#ifndef GR_COLOUR_RENDER_H
#define GR_COLOUR_RENDER_H

#include <Game_Engine/ECS/geComponent.h>

#include <Game_Engine/Graphics/Graphics.h>

typedef struct grColour_Render grColour_Render;

struct grColour_Render {
  geComponent* _super;
  grModel* _model;
  grShader* _shader;
};

grColour_Render* grCreate_Colour_Render(float colour[4], const grMesh* mesh);

// void grDestroy_Colour_Render(grColour_Render* cr);

void grDestroy_Colour_Render_Sub_Component(geComponent* component);

#endif
