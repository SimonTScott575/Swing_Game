#include "Level_4_Basic_Build.h"

Level_4_Basic_Build Level_4_Basic_Build_init(int build_with_physics) {
  return (Level_4_Basic_Build){
    .build_with_physics = build_with_physics
  };
}

void Load_Entity_Player_Level_4_Basic_Build(Level_4_Basic_Build* build) {

  build->player = Create_Player();

}

void Load_Entities_Level_4_Basic_Build(float x, mFrame2D* frame, Level_4_Basic_Build* build) {

  build->player->frame->position.i[0] = x;

  if (build->build_with_physics) {
    build->rope = Create_Rope(build->player->rb);
  }

  build->portal = Create_Portal((mVector2f){{x,0}}, 1);

  for (int i = 0; i < L4_HS_COUNT; i++) {

    float r = L4_MIN_R + (L4_MAX_R - L4_MIN_R)/(i+1);
    float x_pos = r*cos( M_PI*3/4.0f + M_PI/4 * i );
    float y_pos = r*sin( M_PI*3/4.0f + M_PI/4 * i );
    float s = L4_MIN_SCALE + (L4_MAX_SCALE - L4_MIN_SCALE)/(i+1);
    build->hs_arr[i] = Create_Hook_Surface2(
      (mVector2f){{ x + x_pos, y_pos }},
      (mVector2f){{ s, s }}
    );

    build->gems[i] = Create_Gem((mVector2f){{x + x_pos, y_pos + s/2 + 0.5}});
    build->gem_controllers[i] = build->gems[i]->gc;

  }

  build->bg = Create_Background(L4_WIDTH,L4_HEIGHT);
  build->bg->frame->position.i[0] = x;

}

void Set_Level_4_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_4_Basic_Build* build) {

  //
  if (build->build_with_physics) {
    build->rope->rc->rb_sys = rb_sys;
    build->rope->rc->camera2D = camera2D;
  }

  //
  if (build->build_with_physics) {
    Set_Global_Gem_Data(build->gem_controllers, L4_GEM_COUNT,0);
  }
  //
  dAppend_LL(grRenderer_ptr)(build->bg->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->portal->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->player->renderer, rs->_renderers);

  for (int i = 0; i < L4_HS_COUNT; i++) {
    dAppend_LL(grRenderer_ptr)(build->hs_arr[i]->renderer, rs->_renderers);
  }
  for (int i = 0; i < L4_GEM_COUNT; i++) {
    dAppend_LL(grRenderer_ptr)(build->gems[i]->renderer, rs->_renderers);
  }

  if (build->build_with_physics) {
    dAppend_LL(grRenderer_ptr)(build->rope->renderer, rs->_renderers);
  }

  //
  if (build->build_with_physics) {
    phAdd_Rigid_Body2D(build->player->rb, rb_sys);
    phAdd_Rigid_Body2D(build->portal->rb, rb_sys);


    for (int i = 0; i < L4_HS_COUNT; i++) {
      phAdd_Rigid_Body2D(build->hs_arr[i]->rb, rb_sys);
    }
    for (int i = 0; i < L4_GEM_COUNT; i++) {
      phAdd_Rigid_Body2D(build->gems[i]->rb, rb_sys);
    }

    phAdd_Joint2D(&build->rope->spring_j->_super, rb_sys);
    phAdd_Joint2D(&build->rope->rod_j->_super, rb_sys);
  }

}

void Add_Entities_Level_4_Basic_Build(geScene* scene, Level_4_Basic_Build* build) {

  geAdd_Entity(build->player->_super, scene);
  if(build->build_with_physics) {
    geAdd_Entity(build->rope->_super, scene);
  }
  geAdd_Entity(build->portal->_super, scene);

  for (int i = 0; i < L4_HS_COUNT; i++) {
    geAdd_Entity(build->hs_arr[i]->_super,  scene);
  }
  for (int i = 0; i < L4_GEM_COUNT; i++) {
    geAdd_Entity(build->gems[i]->_super,  scene);
  }

  geAdd_Entity(build->bg->_super, scene);

}
