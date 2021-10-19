#include <Game_Engine/Graphics/grColour_Render.h>

#include <stdlib.h>

grColour_Render grColour_Render_init(float colour[4], const grMesh* mesh) {

  grColour_Render cr = {
    ._model = grModel_From_Mesh_init(mesh),
    ._shader = grShader_init("../include/Game_Engine/Graphics/Shaders/grColour_2D_vert.glsl",
                             "../include/Game_Engine/Graphics/Shaders/grColour_2D_frag.glsl") //???TEMP paths...?
  };

  if (colour != NULL) {
    grSet_float4_by_name("grColour", &cr._shader, colour[0], colour[1], colour[2], colour[3]);
  }

  return cr;

}

void grColour_Render_term(grColour_Render* cr) {

  grModel_term(&cr->_model);
  grShader_term(&cr->_shader);

}
