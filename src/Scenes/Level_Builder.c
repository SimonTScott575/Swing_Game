#include "Level_Builder.h"

#include <string.h>

#include "../Glow.h"

#include "../Scenes/End_Level_Menu_Build.h"
#include "../Scenes/Level_UI_Build.h"

#include "../Entities/UI_Camera.h"
#include "../Entities/UI_Manager.h"
#include "../Entities/Menu_Button.h"
#include "../Entities/Timer.h"

#include "../Components/Gem_Controller.h"

Level_Builder Level_Builder_init() {

  return (Level_Builder){
    .as_scene = true,

    .player = NULL,
    .rope = NULL,
    .portal = NULL,
    .gem_arr = NULL, // default : NULL
    .gem_count = 0,
    .hs_arr = NULL, // default : NULL
    .hs_count = 0,
    .hs2_arr = NULL, // default : NULL
    .hs2_count = 0,
    .bg = NULL,

    .instruction_1 = NULL,
    .instruction_2 = NULL,

    .build_level_entities = NULL,
    ._sub = NULL
  };

}

void Build_Level(float x_offset, Level_Builder* builder, geScene* scene) {

  // ========
  // Load ECS
  // ========

  // --------
  // Entities
  // --------

  Build_Level_Basics_Load(x_offset, builder);

  Camera* camera;
  Rope* rope;
  Level_UI_Build level_ui_build;
  End_Level_Menu_Build end_level_menu_build;

  if (builder->as_scene) {

    camera = Create_Camera(builder->player->frame, 20);

    rope = Create_Rope(builder->player->rb);

    //
    Load_Entities_Level_UI_Build(&level_ui_build);

    Load_Entities_End_Level_Menu_Build(builder->portal->pc, level_ui_build.timer->clock, builder->player->pc, &end_level_menu_build);

  }

  // -------
  // Systems
  // -------

  grRendering_System2D* rs;
  phRB_System2D* rb_sys;

  if (builder->as_scene) {

    rs = grCreate_Rendering_System2D(camera->camera2D);

    rb_sys = new_phRB_System2D();

    Load_Systems_Level_UI_Build(&level_ui_build);

    Load_Systems_End_Level_Menu_Build(&end_level_menu_build);

  }

  // ===
  // Set
  // ===

  //
  Build_Level_Basics_Set(rs, builder);

  if (builder->as_scene && builder->instruction_1 != NULL && builder->instruction_2 != NULL) {

    dAppend_LL(grRenderer_ptr)(builder->instruction_1->text_r->_super, rs->_renderers);
    dAppend_LL(grRenderer_ptr)(builder->instruction_2->text_r->_super, rs->_renderers);

  }

  if (builder->as_scene) {

    dAppend_LL(grRenderer_ptr)(rope->renderer, rs->_renderers);

    phAdd_Rigid_Body2D(builder->player->rb, rb_sys);
    phAdd_Rigid_Body2D(builder->portal->rb, rb_sys);
    for (int i = 0; i < builder->hs_count; i++) {
      phAdd_Rigid_Body2D(builder->hs_arr[i]->rb, rb_sys);
    }
    for (int i = 0; i < builder->hs2_count; i++) {
      phAdd_Rigid_Body2D(builder->hs2_arr[i]->rb, rb_sys);
    }
    for (int i = 0; i < builder->gem_count; i++) {
      phAdd_Rigid_Body2D(builder->gem_arr[i]->rb, rb_sys);
    }
    phAdd_Joint2D(&rope->spring_j->_super, rb_sys);
    phAdd_Joint2D(&rope->rod_j->_super, rb_sys);

    rope->rc->rb_sys = rb_sys;
    rope->rc->camera2D = camera->camera2D;

    rs->post_process = Glow_PP;
    Gem_Controller** gc_arr = malloc(builder->gem_count * sizeof *gc_arr);
    for (int i = 0; i < builder->gem_count; i++) {
      gc_arr[i] = builder->gem_arr[i]->gc;
    }
    Set_Global_Gem_Data(gc_arr, builder->gem_count, 0);
    free(gc_arr);

    //
    camera->cc->rs = rs;

    rb_sys->gravity = (mVector2f){{0,-5}};

    //
    Set_Level_UI_Build(&level_ui_build);

    //
    Set_End_Level_Menu_Build(&end_level_menu_build);

  }

  // ===
  // Add
  // ===

  // -------
  // Entites
  // -------

  Build_Level_Basics_Add(scene, builder);

  if (builder->as_scene) {
    geAdd_Entity(camera->_super, scene);
    geAdd_Entity(rope->_super, scene);

    Add_Entities_Level_UI_Build(scene, &level_ui_build);

    Add_Entities_End_Level_Menu_Build(scene, &end_level_menu_build);

  }

  // -------
  // Systems
  // -------

  if (builder->as_scene) {

    geAdd_System(rs->_super, scene);
    geAdd_System(rb_sys->_super, scene);

    Add_Systems_Level_UI_Build(scene, &level_ui_build);

    Add_Systems_End_Level_Menu_Build(scene, &end_level_menu_build);

  }

  

}

void Build_Level_Basics_Load(float x_offset, Level_Builder* builder) {

  builder->build_level_entities(builder);

  builder->player->frame->position.i[0] += x_offset;
  builder->portal->frame->position.i[0] += x_offset;
  if (builder->bg != NULL) {
    builder->bg->frame->position.i[0] += x_offset;
  }
  for (int i = 0; i < builder->gem_count; i++) {
    builder->gem_arr[i]->frame->position.i[0] += x_offset;
  }
  for (int i = 0; i < builder->hs_count; i++) {
    builder->hs_arr[i]->frame->position.i[0] += x_offset;
  }
  for (int i = 0; i < builder->hs2_count; i++) {
    builder->hs2_arr[i]->frame->position.i[0] += x_offset;
  }

}

void Build_Level_Basics_Set(grRendering_System2D* rs, Level_Builder* builder) {

  // memcpy(rs->camera->background_colour,
  //        builder->bg_colour,
  //        4*sizeof(float));

  if (builder->bg != NULL) {
    dAppend_LL(grRenderer_ptr)(builder->bg->renderer, rs->_renderers);
  }

  dAppend_LL(grRenderer_ptr)(builder->portal->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(builder->player->renderer, rs->_renderers);

  for (int i = 0; i < builder->hs_count; i++) {
    dAppend_LL(grRenderer_ptr)(builder->hs_arr[i]->renderer, rs->_renderers);
  }
  for (int i = 0; i < builder->hs2_count; i++) {
    dAppend_LL(grRenderer_ptr)(builder->hs2_arr[i]->renderer, rs->_renderers);
  }
  for (int i = 0; i < builder->gem_count; i++) {
    dAppend_LL(grRenderer_ptr)(builder->gem_arr[i]->renderer, rs->_renderers);
  }

}

void Build_Level_Basics_Add(geScene* scene, Level_Builder* builder) {

  geAdd_Entity(builder->player->_super, scene);
  geAdd_Entity(builder->portal->_super, scene);

  for (int i = 0; i < builder->hs_count; i++) {
    geAdd_Entity(builder->hs_arr[i]->_super,  scene);
  }
  for (int i = 0; i < builder->hs2_count; i++) {
    geAdd_Entity(builder->hs2_arr[i]->_super,  scene);
  }
  for (int i = 0; i < builder->gem_count; i++) {
    geAdd_Entity(builder->gem_arr[i]->_super,  scene);
  }
  if (builder->bg != NULL) {
    geAdd_Entity(builder->bg->_super, scene);
  }

  if (builder->as_scene && builder->instruction_1 != NULL && builder->instruction_2 != NULL) {
    geAdd_Entity(builder->instruction_1->_super, scene);
    geAdd_Entity(builder->instruction_2->_super, scene);
  }

}
