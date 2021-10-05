#include "Level_3_Basic_Build.h"

Level_3_Basic_Build Level_3_Basic_Build_init(int build_with_physics) {
  return (Level_3_Basic_Build){
    .build_with_physics = build_with_physics
  };
}

void Load_Entity_Player_Level_3_Basic_Build(Level_3_Basic_Build* build) {

  build->player = Create_Player();

}

void Load_Entities_Level_3_Basic_Build(float x, mFrame2D* frame, Level_3_Basic_Build* build) {

  build->player->frame->position.i[0] = x;

  if (build->build_with_physics) {
    build->rope = Create_Rope(build->player->rb);
  }

  build->portal = Create_Portal((mVector2f){{x,0}}, 1);

  build->hs1 = Create_Hook_Surface(
    (mVector2f){{ x, L3_HEIGHT/2 + L3_BUFFER/2 }},
    (mVector2f){{ L3_TOTAL + L3_BUFFER*2, L3_BUFFER }}
  );
  build->hs2 = Create_Hook_Surface(
    (mVector2f){{ x, -L3_HEIGHT/2  - L3_BUFFER/2 }},
    (mVector2f){{ L3_TOTAL + L3_BUFFER*2, L3_BUFFER }}
  );
  build->hs3 = Create_Hook_Surface(
    (mVector2f){{ x - L3_WIDTH/2 - L3_BUFFER/2, 0 }},
    (mVector2f){{ L3_BUFFER, L3_HEIGHT }}
  );
  build->hs4 = Create_Hook_Surface(
    (mVector2f){{ x + L3_WIDTH/2 + L3_BUFFER/2, 0 }},
    (mVector2f){{ L3_BUFFER, L3_HEIGHT }}
  );

  for (int i = 0; i < L3_PILLAR1_COLS; i++) {

    build->hs_pillars[i] = Create_Hook_Surface(
      (mVector2f){{ x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A, 0 }},
      (mVector2f){{ L3_C, L3_F }}
    );

    build->gems[2*i] = Create_Gem((mVector2f){{
      x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A,
      L3_F/2 + L3_E/2
    }});
    build->gems[2*i+1] = Create_Gem((mVector2f){{
      x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A,
      - L3_F/2 - L3_E/2
    }});

  }
  int j = 0;
  for (int i = 0; i < L3_PILLAR1_COLS-1; i++) {

    build->hs_pillars[L3_PILLAR1_COLS + 2*i] = Create_Hook_Surface(
      (mVector2f){{ x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A, L3_F/2+L3_E/2 }},
      (mVector2f){{ L3_C, L3_E }}
    );
    build->hs_pillars[L3_PILLAR1_COLS + 2*i+1] = Create_Hook_Surface(
      (mVector2f){{ x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A, -L3_F/2-L3_E/2 }},
      (mVector2f){{ L3_C, L3_E }}
    );

    if (i != L3_PILLAR1_COLS/2 - 1) {

      build->gems[2*L3_PILLAR1_COLS + j] = Create_Gem((mVector2f){{
        x - 2*L3_A*L3_PILLAR1_COLS/2 + L3_A + i*2*L3_A + L3_A,
        0
      }});

      j += 1;

    }

  }

  build->bg = Create_Background(L3_WIDTH,L3_HEIGHT);
  build->bg->frame->position.i[0] = x;

}

void Set_Level_3_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_3_Basic_Build* build) {

  //
  if (build->build_with_physics) {
    build->rope->rc->rb_sys = rb_sys;
    build->rope->rc->camera2D = camera2D;
  }

  //
  gems_count = L3_GEM_COUNT;
  gems_caught_count = 0;
  //
  dAppend_LL(grRenderer_ptr)(build->bg->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->portal->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->player->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->hs1->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs2->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs3->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs4->renderer, rs->_renderers);
  for (int i = 0; i < L3_PILLAR_COUNT; i++) { // L3_PILLAR_COUNT
    dAppend_LL(grRenderer_ptr)(build->hs_pillars[i]->renderer, rs->_renderers);
  }
  for (int i = 0; i < L3_GEM_COUNT; i++) { // L3_PILLAR_COUNT
    dAppend_LL(grRenderer_ptr)(build->gems[i]->renderer, rs->_renderers);
  }

  if (build->build_with_physics) {
    dAppend_LL(grRenderer_ptr)(build->rope->renderer, rs->_renderers);
  }

  //
  if (build->build_with_physics) {
    phAdd_Rigid_Body2D(build->player->rb, rb_sys);
    phAdd_Rigid_Body2D(build->portal->rb, rb_sys);

    phAdd_Rigid_Body2D(build->hs1->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs2->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs3->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs4->rb, rb_sys);
    for (int i = 0; i < L3_PILLAR_COUNT; i++) { // L3_PILLAR_COUNT
      phAdd_Rigid_Body2D(build->hs_pillars[i]->rb, rb_sys);
    }
    for (int i = 0; i < L3_GEM_COUNT; i++) { // L3_PILLAR_COUNT
      phAdd_Rigid_Body2D(build->gems[i]->rb, rb_sys);
    }

    phAdd_Joint2D(&build->rope->spring_j->_super, rb_sys);
    phAdd_Joint2D(&build->rope->rod_j->_super, rb_sys);
  }

}

void Add_Entities_Level_3_Basic_Build(geScene* scene, Level_3_Basic_Build* build) {

  geAdd_Entity(build->player->_super, scene);
  if(build->build_with_physics) {
    geAdd_Entity(build->rope->_super, scene);
  }
  geAdd_Entity(build->portal->_super, scene);

  geAdd_Entity(build->hs1->_super,  scene);
  geAdd_Entity(build->hs2->_super,  scene);
  geAdd_Entity(build->hs3->_super,  scene);
  geAdd_Entity(build->hs4->_super,  scene);
  for (int i = 0; i < L3_PILLAR_COUNT; i++) { // L3_PILLAR_COUNT
    geAdd_Entity(build->hs_pillars[i]->_super,  scene);
  }
  for (int i = 0; i < L3_GEM_COUNT; i++) {
    geAdd_Entity(build->gems[i]->_super,  scene);
  }

  geAdd_Entity(build->bg->_super, scene);

}
