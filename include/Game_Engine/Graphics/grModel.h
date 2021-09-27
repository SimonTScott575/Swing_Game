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

// ====================
// Creation/Destruction
// ====================

// // Upload Mesh at path to GPU
// // Valid file formats: .obj (partially supported)
// grModel* grCreate_Model(const char* path);

// Combine meshs into one and upload to GPU memory
grModel* grCreate_Model_From_Mesh(const grMesh* meshes);
/*** LEGACY ***/
// #define grCreate_Model_From_Meshes(A,B) grCreate_Model_From_Mesh(*A)
/**************/

// Deletes model from GPU, frees model pointer
void grDestroy_Model(grModel* model);

#endif
