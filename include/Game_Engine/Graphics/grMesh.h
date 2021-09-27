#ifndef GR_MESH_H
#define GR_MESH_H

#include <stdint.h>

#include <Game_Engine/Graphics/Formats/grTypes.h>

typedef struct grMesh grMesh;
struct grMesh {
  void* vertices_data;
  uint32_t* indices;

  grType* types;
  uint32_t* counts;

  uint32_t vertices_data_length;
  uint32_t indices_length;
  uint32_t types_length;

  size_t* offsets;
  size_t size_of_vertex;
};

extern const grMesh* const grRect2D_Mesh;
extern const grMesh* const grRect2D_2_Mesh;

void grInit_Mesh();

#endif
