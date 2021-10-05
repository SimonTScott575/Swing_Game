#include "Level_2_Basic_Build.h"

Level_2_Basic_Build Level_2_Basic_Build_init(int build_with_physics) {
  return (Level_2_Basic_Build){
    .build_with_physics = build_with_physics
  };
}

void Load_Entity_Player_Level_2_Basic_Build(Level_2_Basic_Build* build) {

  build->player = Create_Player();

}

void Load_Entities_Level_2_Basic_Build(float x, mFrame2D* frame, Level_2_Basic_Build* build) {

  build->player->frame->position.i[0] = x;

  if (build->build_with_physics) {
    build->rope = Create_Rope(build->player->rb);
  }

  build->gem1 = Create_Gem((mVector2f){{x +  L2_A, 0}});
  build->gem2 = Create_Gem((mVector2f){{x + -L2_A, 0}});
  build->gem3 = Create_Gem((mVector2f){{x +  0, L2_A}});
  build->gem4 = Create_Gem((mVector2f){{x +  0,-L2_A}});

  build->portal = Create_Portal((mVector2f){{x,0}}, 1);

  build->hs1 = Create_Hook_Surface(
    (mVector2f){{ x, -L2_HW-L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }}
  );
  build->hs2 = Create_Hook_Surface(
    (mVector2f){{ x, L2_HW+L2_BUFFER/2 }},
    (mVector2f){{ L2_HW*2+L2_BUFFER*2, L2_BUFFER }}
  );
  build->hs3 = Create_Hook_Surface(
    (mVector2f){{ x -L2_HW-L2_BUFFER/2,  0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }}
  );
  build->hs4 = Create_Hook_Surface(
    (mVector2f){{ x + L2_HW+L2_BUFFER/2, 0 }},
    (mVector2f){{ L2_BUFFER, L2_HW*2 }}
  );
  build->hs5 = Create_Hook_Surface(
    (mVector2f){{ x + L2_C+L2_B/2, L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }}
  );
  build->hs6 = Create_Hook_Surface(
    (mVector2f){{ x - (L2_C+L2_B/2), L2_C+L2_B/2 }},
    (mVector2f){{ L2_B, L2_B }}
  );
  build->hs7 = Create_Hook_Surface(
    (mVector2f){{ x - (L2_C+L2_B/2), -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }}
  );
  build->hs8 = Create_Hook_Surface(
    (mVector2f){{ x + L2_C+L2_B/2, -(L2_C+L2_B/2) }},
    (mVector2f){{ L2_B, L2_B }}
  );

  build->bg = Create_Background(L2_TOTAL,L2_TOTAL);
  build->bg->frame->position.i[0] = x;

}

void Set_Level_2_Basic_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_2_Basic_Build* build) {

  //
  if (build->build_with_physics) {
    build->rope->rc->rb_sys = rb_sys;
    build->rope->rc->camera2D = camera2D;
  }

  //
  gems_count = 4;
  gems_caught_count = 0;
  //
  dAppend_LL(grRenderer_ptr)(build->bg->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->portal->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->player->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->hs1->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs2->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs3->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs4->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs5->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs6->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs7->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs8->renderer, rs->_renderers);

  if (build->build_with_physics) {
    dAppend_LL(grRenderer_ptr)(build->rope->renderer, rs->_renderers);
  }

  dAppend_LL(grRenderer_ptr)(build->gem1->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->gem2->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->gem3->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->gem4->renderer, rs->_renderers);

  //
  if (build->build_with_physics) {
    phAdd_Rigid_Body2D(build->player->rb, rb_sys);
    phAdd_Rigid_Body2D(build->portal->rb, rb_sys);

    phAdd_Rigid_Body2D(build->gem1->rb, rb_sys);
    phAdd_Rigid_Body2D(build->gem2->rb, rb_sys);
    phAdd_Rigid_Body2D(build->gem3->rb, rb_sys);
    phAdd_Rigid_Body2D(build->gem4->rb, rb_sys);

    phAdd_Rigid_Body2D(build->hs1->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs2->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs3->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs4->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs5->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs6->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs7->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs8->rb, rb_sys);

    phAdd_Joint2D(&build->rope->spring_j->_super, rb_sys);
    phAdd_Joint2D(&build->rope->rod_j->_super, rb_sys);
  }

}

void Add_Entities_Level_2_Basic_Build(geScene* scene, Level_2_Basic_Build* build) {

  geAdd_Entity(build->player->_super, scene);
  if(build->build_with_physics) {
    geAdd_Entity(build->rope->_super, scene);
  }
  geAdd_Entity(build->portal->_super, scene);

  geAdd_Entity(build->gem1->_super, scene);
  geAdd_Entity(build->gem2->_super, scene);
  geAdd_Entity(build->gem3->_super, scene);
  geAdd_Entity(build->gem4->_super, scene);

  geAdd_Entity(build->hs1->_super,  scene);
  geAdd_Entity(build->hs2->_super,  scene);
  geAdd_Entity(build->hs3->_super,  scene);
  geAdd_Entity(build->hs4->_super,  scene);
  geAdd_Entity(build->hs5->_super,  scene);
  geAdd_Entity(build->hs6->_super,  scene);
  geAdd_Entity(build->hs7->_super,  scene);
  geAdd_Entity(build->hs8->_super,  scene);

  geAdd_Entity(build->bg->_super, scene);

}
