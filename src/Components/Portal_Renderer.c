#include "Portal_Renderer.h"

#include "Gem_Controller.h"

Portal_Renderer* Create_Portal_Renderer() {

  Portal_Renderer* pr = malloc(sizeof(Portal_Renderer));

  *pr = (Portal_Renderer){
    .grey_t = grCreate_Texture("../Resources/Textures/ring_grey_256.png"),
    .white_t = grCreate_Texture("../Resources/Textures/ring_white_256.png"),

    .model = grCreate_Model_From_Mesh(grRect2D_Mesh),
    .shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grTexture_2D_vert.glsl",
                              "../include/Game_Engine/Graphics/Shaders/grTexture_2D_frag.glsl")
  };

  pr->_super = geCreate_Component();
  geSet_Sub_Component(pr, Update_Portal_Renderer, Destroy_Portal_Renderer_Sub_Component, pr->_super);

  grSet_Texture_by_name("grTexture", pr->grey_t, pr->shader);

  return pr;

}

void Update_Portal_Renderer(geComponent* component) {

  Portal_Renderer* pr = component->_sub;

  if ( gems_caught_count >= gems_count ) {
    grSet_Texture_by_name("grTexture", pr->white_t, pr->shader);
  }

}

void Destroy_Portal_Renderer_Sub_Component(geComponent* component) {

  Portal_Renderer* pr = component->_sub;

  grDestroy_Texture(pr->grey_t);
  grDestroy_Texture(pr->white_t);
  grDestroy_Model(pr->model);
  grDestroy_Shader(pr->shader);

  free(pr);

}
