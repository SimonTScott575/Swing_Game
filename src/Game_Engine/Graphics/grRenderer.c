#include <Game_Engine/Graphics/grRenderer.h>

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

D_SOURCE_LLIST(grRenderer*, grRenderer_ptr);

// ====================
// Creation/Destruction
// ====================

void grRenderer_2D_ctor(grRenderer* self, mFrame2D* frame, grModel* model, grShader* shader) {

  *self = (grRenderer){

    .is_active = true,
    ._renderer_node = NULL,

    .frame = frame,
    .model = model,
    .shader = shader,
    .Z = 0,

    .render_fn = grRender_2D,

    ._destroy_sub = NULL,
    ._sub = NULL

  };

  geComponent_ctor(&self->_super);

  geSet_Sub_Component(self, NULL, grRenderer_Sub_Component_dtor, &self->_super);

}

// grRenderer* grCreate_Renderer_3D(mFrame3D* frame, grModel* model, grShader* shader) {
//
//   grRenderer* renderer = malloc(sizeof(grRenderer));
//   *renderer = (grRenderer){
//
//     ._super = geCreate_Component(renderer, NULL, grDestroy_Renderer_void),
//
//     .frame = frame,
//     .model = model,
//     .shader = shader,
//     .Z = 0,
//
//     .render_fn = grRender_3D,
//
//     ._destroy_sub = NULL,
//     ._sub = NULL
//
//   };
//
//   return renderer;
//
// }

// void grDestroy_Renderer(grRenderer* renderer) {
//
//   geDestroy_Component(renderer->_super);
//
//   if (renderer->_destroy_sub != NULL) {
//     renderer->_destroy_sub(renderer);
//   }
//
//   free(renderer);
//
// }

void grRenderer_Sub_Component_dtor(geComponent* component) {

  grRenderer* renderer = component->_sub;

  if (renderer->_destroy_sub != NULL) {
    renderer->_destroy_sub(renderer);
  }

}

// ===

void grSet_Sub_Renderer(void* sub, grRender_fn render, grDestroy_Sub_Renderer_fn destroy, grRenderer* renderer) {
  renderer->_sub = sub;
  renderer->render_fn = render;
  renderer->_destroy_sub = destroy;
}

// ======
// Render
// ======

void grRender(grRenderer* renderer, grCamera2D* camera) {
  renderer->render_fn(renderer, camera);
}

// ONLY call when renderer->frame holds mFrame2D
void grRender_2D(grRenderer* renderer, grCamera2D* camera) {

  mGenerate_transform_2D(renderer->frame);

  glUseProgram(renderer->shader->_OpenGL_ID);

  uint32_t textures_length = renderer->shader->_textures_length;
  for (uint32_t i = 0; i < textures_length; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, renderer->shader->textures[i]->_OpenGL_ID);
  }

  glUniformMatrix3fv(renderer->shader->_View3x3_location,       1, GL_TRUE, (const GLfloat *) camera->View3x3.i);
  glUniformMatrix3fv(renderer->shader->_Projection3x3_location, 1, GL_TRUE, (const GLfloat *) camera->Projection3x3.i);
  glUniformMatrix3fv(renderer->shader->_Model3x3_location, 1, GL_TRUE, (const GLfloat *) ((mFrame2D*) renderer->frame)->transform.i);
  glUniform1f(renderer->shader->_Z_location, renderer->Z);

  glBindVertexArray(renderer->model->_OpenGL_IDs.VAO);

  glDrawElements(GL_TRIANGLES, renderer->model->indices_length, GL_UNSIGNED_INT, 0);

};
// // ONLY call when renderer->frame holds mFrame3D
// void grRender_3D(grRenderer* renderer) { //??? has this been tested ?
//
//   glUseProgram(renderer->shader->_OpenGL_ID);
//
//   uint32_t textures_length = renderer->shader->_textures_length;
//   for (uint32_t i = 0; i < textures_length; i++) {
//     glActiveTexture(GL_TEXTURE0 + i);
//     glBindTexture(GL_TEXTURE_2D, renderer->shader->textures[i]->_OpenGL_ID);
//   }
//
//   mGenerate_transform_3D((mFrame3D*) renderer->frame);
//   glUniformMatrix4fv(renderer->shader->_Model4x4_location, 1, GL_TRUE, (const GLfloat *) ((mFrame3D*) renderer->frame)->transform.i);
//
//   glUniform1f(renderer->shader->_Z_location, renderer->Z);
//
//   glBindVertexArray(renderer->model->_OpenGL_IDs.VAO);
//
//   glDrawElements(GL_TRIANGLES, renderer->model->indices_length, GL_UNSIGNED_INT, 0);
//
// };
