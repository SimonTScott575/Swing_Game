#include <Game_Engine/Graphics/Defaults/grSprite.h>

#include <stdlib.h>

// static void grDestroy_Sprite_void(void* arg) {
//   grDestroy_Sprite(arg);
// }

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
  // sprite->_model = grCreate_Model("include/Game_Engine/Graphics/Meshes/grRect2D.obj");

  sprite->_shader = grCreate_Shader("../include/Game_Engine/Graphics/Shaders/grTexture_2D_vert.glsl",
                                    "../include/Game_Engine/Graphics/Shaders/grTexture_2D_frag.glsl"); //!!!TEMP paths...?
  grSet_Texture_by_name("grTexture", sprite->_texture, sprite->_shader);

  // *sprite = (grSprite){
  //   ._texture = grCreate_Texture(path),
  //   ._model = grCreate_Model("include/Game_Engine/Graphics/Meshes/grRect2D.obj"),
  //   ._shader = grCreate_Shader("include/Game_Engine/Graphics/Shaders/grTexture_2D_vert.glsl",
  //                              "include/Game_Engine/Graphics/Shaders/grTexture_2D_frag.glsl")
  // };

  sprite->_super = geCreate_Component();
  geSet_Sub_Component(sprite, NULL, grDestroy_Sprite_Sub_Component, sprite->_super);

  return sprite;

}

// void grDestroy_Sprite(grSprite* sprite) {
//
//   geDestroy_Component(sprite->_super);
//
//   grDestroy_Texture(sprite->_texture);
//   grDestroy_Model(sprite->_model);
//   grDestroy_Shader(sprite->_shader);
//
//   free(sprite);
//
// }

void grDestroy_Sprite_Sub_Component(geComponent* component) {

  grSprite* sprite = component->_sub;

  grDestroy_Texture(sprite->_texture);
  grDestroy_Model(sprite->_model);
  grDestroy_Shader(sprite->_shader);

  free(sprite);

}
