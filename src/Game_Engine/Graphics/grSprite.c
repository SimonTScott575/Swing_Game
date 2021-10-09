#include <Game_Engine/Graphics/grSprite.h>

#include <stdlib.h>

grSprite* grCreate_Sprite(char* path, float width, float height) {

  grSprite* sprite = malloc(sizeof(grSprite));

  sprite->_texture = grCreate_Texture(path);

  float hw = width/2;
  float hh = height/2;

  grMesh mesh = {
    .vertices_data = (float[4*4]){
      -hw,-hh, 0,0,
       hw, hh, 1,1,
      -hw, hh, 0,1,
       hw,-hh, 1,0
     },
    .indices = (uint32_t[6]){0,1,2, 0,3,1},

    .types = (grType[2]){grTypes._float, grTypes._float},
    .counts = (uint32_t[2]){2,2},

    .vertices_data_length = 4,
    .indices_length = 6,
    .types_length = 2,

    .offsets = (size_t[2]){0,2*sizeof(float)},
    .size_of_vertex = 4*sizeof(float)
  };

  sprite->_model = grCreate_Model_From_Mesh(&mesh);

  sprite->_shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grTexture_2D_vert.glsl",
                                    "../include/Game_Engine/Graphics/Shaders/grTexture_2D_frag.glsl"); //!!!TEMP paths...?
  grSet_Texture_by_name("grTexture", sprite->_texture, sprite->_shader);

  return sprite;

}

void grDestroy_Sprite(grSprite* sprite) {

  grDestroy_Texture(sprite->_texture);
  grDestroy_Model(sprite->_model);
  grDestroy_Shader(sprite->_shader);

  free(sprite);

}
