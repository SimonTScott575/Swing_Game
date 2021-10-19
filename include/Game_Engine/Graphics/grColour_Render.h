#ifndef GR_COLOUR_RENDER_H
#define GR_COLOUR_RENDER_H

#include <Game_Engine/Graphics/grModel.h>
#include <Game_Engine/Graphics/grShader.h>

typedef
struct grColour_Render {
  grModel _model;
  grShader _shader;
} grColour_Render;

grColour_Render grColour_Render_init(float colour[4], const grMesh* mesh);

void grColour_Render_term(grColour_Render* cr);

#endif
