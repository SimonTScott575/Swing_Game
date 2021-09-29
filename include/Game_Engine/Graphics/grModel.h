#ifndef GR_MODEL_H
#define GR_MODEL_H

#include <stdint.h>

#include "grMesh.h"

typedef struct grModel grModel;
struct grModel {
  uint32_t indices_length;

  struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
  } _OpenGL_IDs;
};

// ==========================
// Initialization/Termination
// ==========================

// Uploads mesh to GPU RAM.
grModel* grCreate_Model_From_Mesh(const grMesh* meshes);

// Frees all model data from CPU/GPU RAM.
void grDestroy_Model(grModel* model);

#endif
