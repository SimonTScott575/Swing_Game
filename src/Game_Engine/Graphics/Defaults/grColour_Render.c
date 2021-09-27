#include <Game_Engine/Graphics/Defaults/grColour_Render.h>

#include <stdlib.h>

// static void grDestroy_Colour_Render_void(void* arg) {
//   grDestroy_Colour_Render(arg);
// }

grColour_Render* grCreate_Colour_Render(float colour[4], const grMesh* mesh) {

  grColour_Render* cr = malloc(sizeof(grColour_Render));

  *cr = (grColour_Render){
    ._model = grCreate_Model_From_Mesh(mesh),
    ._shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grColour_2D_vert.glsl",
                               "../include/Game_Engine/Graphics/Shaders/grColour_2D_frag.glsl") //???TEMP paths...?
  };

  cr->_super = geCreate_Component();
  geSet_Sub_Component(cr, NULL, grDestroy_Colour_Render_Sub_Component, cr->_super);

  if (colour != NULL) {
    grSet_float4_by_name("grColour", cr->_shader, colour[0], colour[1], colour[2], colour[3]);
  }

  return cr;

}

// void grDestroy_Colour_Render(grColour_Render* cr) {
//
//   geDestroy_Component(cr->_super);
//
//   grDestroy_Model(cr->_model);
//   grDestroy_Shader(cr->_shader);
//
//   free(cr);
//
// }
void grDestroy_Colour_Render_Sub_Component(geComponent* component) {

  grColour_Render* cr = component->_sub;

  grDestroy_Model(cr->_model);
  grDestroy_Shader(cr->_shader);

  free(cr);

}
