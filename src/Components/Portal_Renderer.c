#include "Portal_Renderer.h"

#include "Gem_Controller.h"

void Portal_Renderer_ctor(Portal_Renderer* self) {

  *self = (Portal_Renderer){
    .grey_t = grCreate_Texture("../Resources/Textures/ring_grey_512.png"),
    .white_t = grCreate_Texture("../Resources/Textures/ring_white_blur_512.png"),

    .model = grCreate_Model_From_Mesh(grRect2D_2_Mesh),
    .shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grTexture_2D_vert.glsl",
                              "../include/Game_Engine/Graphics/Shaders/grTexture_2D_frag.glsl")
  };

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Portal_Renderer, Portal_Renderer_Sub_Component_dtor, &self->_super);

  grSet_Texture_by_name("grTexture", self->grey_t, self->shader);

}

void Update_Portal_Renderer(geComponent* component) {

  Portal_Renderer* pr = component->_sub;

  if ( g_gems_caught_count >= g_gems_count ) {
    grSet_Texture_by_name("grTexture", pr->white_t, pr->shader);
  }

}

void Portal_Renderer_Sub_Component_dtor(geComponent* component) {

  Portal_Renderer* pr = component->_sub;

  grDestroy_Texture(pr->grey_t);
  grDestroy_Texture(pr->white_t);
  grDestroy_Model(pr->model);
  grDestroy_Shader(pr->shader);

}
