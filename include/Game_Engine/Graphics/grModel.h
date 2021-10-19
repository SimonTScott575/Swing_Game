#ifndef GR_MODEL_H
#define GR_MODEL_H

#include <stdint.h>

#include "grMesh.h"

typedef
struct grModel {
  uint32_t indices_length;

  struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
  } _OpenGL_IDs;
} grModel;

// ==========================
// Initialization/Termination
// ==========================

// Uploads mesh to GPU RAM.
grModel grModel_From_Mesh_init(const grMesh* meshes);

// Frees all model data from CPU/GPU RAM.
void grModel_term(grModel* model);

#endif
