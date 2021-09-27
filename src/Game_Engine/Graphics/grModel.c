#include <Game_Engine/Graphics/grModel.h>

//TODO: remove code duplication, put loading code in seperate static fn or module ?

#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ====================
// Creation/Destruction
// ====================

grModel* grCreate_Model_From_Mesh(const grMesh* mesh) {

  // Set model properties
  grModel* model = malloc(sizeof(grModel));
  model->indices_length = mesh->indices_length;

  // Prepare buffers
  glGenVertexArrays(1, &model->_OpenGL_IDs.VAO);
  glGenBuffers(1, &model->_OpenGL_IDs.VBO);
  glGenBuffers(1, &model->_OpenGL_IDs.EBO);

  glBindVertexArray(model->_OpenGL_IDs.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, model->_OpenGL_IDs.VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->_OpenGL_IDs.EBO);

  // Send data to GPU
  size_t size_of_vertices = mesh->size_of_vertex * mesh->vertices_data_length;
  size_t size_of_indices = sizeof(uint32_t) * mesh->indices_length;
  glBufferData(GL_ARRAY_BUFFER, size_of_vertices, mesh->vertices_data, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices, mesh->indices, GL_STATIC_DRAW);

  // Pass data format
  for (int i = 0; i < mesh->types_length; i++) {
    glVertexAttribPointer(i, mesh->counts[i], mesh->types[i], GL_FALSE, mesh->size_of_vertex, (void*) mesh->offsets[i]);
    glEnableVertexAttribArray(i);
  }

  return model;

}

void grDestroy_Model(grModel* model) {

  glDeleteVertexArrays(1, &model->_OpenGL_IDs.VAO);
  glDeleteBuffers(1, &model->_OpenGL_IDs.VBO);
  glDeleteBuffers(1, &model->_OpenGL_IDs.EBO);

  free(model);

}
