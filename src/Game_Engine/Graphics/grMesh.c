#include <Game_Engine/Graphics/grMesh.h>

#include <stdlib.h>

static grMesh grRect2D_Mesh_inst = {
  .vertices_data = (float[4*4]){
    -0.5,-0.5, 0,0,
     0.5, 0.5, 1,1,
    -0.5, 0.5, 0,1,
     0.5,-0.5, 1,0
  },
  .indices = (uint32_t[6]){0,1,2, 0,3,1},

  // types: see init
  .counts = (uint32_t[2]){2,2},

  .vertices_data_length = 4,
  .indices_length = 6,
  .types_length = 2,

  .offsets = (size_t[2]){0,2*sizeof(float)},
  .size_of_vertex = 4*sizeof(float)
};
static grMesh grRect2D_2_Mesh_inst = {
  .vertices_data = (float[4*4]){
    -1,-1, 0,0,
     1, 1, 1,1,
    -1, 1, 0,1,
     1,-1, 1,0
  },
  .indices = (uint32_t[6]){0,1,2, 0,3,1},

  // types: see init
  .counts = (uint32_t[2]){2,2},

  .vertices_data_length = 4,
  .indices_length = 6,
  .types_length = 2,

  .offsets = (size_t[2]){0,2*sizeof(float)},
  .size_of_vertex = 4*sizeof(float)
};

const grMesh* const grRect2D_Mesh = &grRect2D_Mesh_inst;
const grMesh* const grRect2D_2_Mesh = &grRect2D_2_Mesh_inst;

void grInit_Mesh() {

  grRect2D_Mesh_inst.types = malloc(2*sizeof(grType));
  grRect2D_Mesh_inst.types[0] = grTypes._float;
  grRect2D_Mesh_inst.types[1] = grTypes._float;
  grRect2D_2_Mesh_inst.types = malloc(2*sizeof(grType));
  grRect2D_2_Mesh_inst.types[0] = grTypes._float;
  grRect2D_2_Mesh_inst.types[1] = grTypes._float;

}
