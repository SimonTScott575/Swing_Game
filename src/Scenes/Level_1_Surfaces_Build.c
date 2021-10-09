#include "Level_1_Surfaces_Build.h"

Level_1_Surfaces_Build Level_1_Surfaces_Build_init(int build_with_physics) {
  return (Level_1_Surfaces_Build){
    .build_with_physics = build_with_physics
  };
}

void Load_Entity_Player_Level_1_Surfaces_Build(float x, Level_1_Surfaces_Build* build) {

  build->player = Create_Player();
  build->player->frame->position.i[0] = x;

}

void Load_Entities_Level_1_Surfaces_Build(float x, mFrame2D* frame, Camera_Controller* cc, Level_1_Surfaces_Build* build) {

  if (build->build_with_physics) { build->rope = Create_Rope(build->player->rb); }

  build->hs1 = Create_Hook_Surface(
    (mVector2f){{ x, -L1_E/2-L1_D - L1_BUFFER/2 }},
    (mVector2f){{L1_TOTAL+L1_BUFFER*2, L1_BUFFER}}
  );
  build->hs2 = Create_Hook_Surface(
    (mVector2f){{ x, L1_E/2+L1_D + L1_BUFFER/2 }},
    (mVector2f){{L1_TOTAL+L1_BUFFER*2, L1_BUFFER}}
  );
  build->hs3 = Create_Hook_Surface(
    (mVector2f){{ x - L1_A/2 - L1_BUFFER/2, 0 }},
    (mVector2f){{L1_BUFFER, L1_D+2*L1_E}}
  );
  build->hs4 = Create_Hook_Surface(
    (mVector2f){{ x + L1_TOTAL-L1_A/2 + L1_BUFFER/2, 0 }},
    (mVector2f){{L1_BUFFER, L1_D+2*L1_E}}
  );
  build->hs5 = Create_Hook_Surface(
    (mVector2f){{ x + L1_A/2 + L1_B/2, -L1_E/2 - L1_D/2 }},
    (mVector2f){{L1_B, L1_D}}
  );
  build->hs6 = Create_Hook_Surface(
    (mVector2f){{ x + L1_A/2 + L1_B + L1_C + L1_B/2, L1_E/2 + L1_D/2 }},
    (mVector2f){{L1_B, L1_D}}
   );

  mVector2f gem_positions[1] = {
    (mVector2f){{x + L1_A/2 + L1_B + L1_C/2,0}}
  };
  build->gem  = Create_Gem(gem_positions[0]);
  // if (cc != NULL) {
  //   Set_Gem_Positions(gem_positions, 1, cc);
  // }

  // gems_count = 1;
  // gems_caught_count = 0;
  if (build->build_with_physics) {
    Set_Global_Gem_Data(&build->gem->gc, 1,0);
  }

  build->portal = Create_Portal((mVector2f){{x + L1_TOTAL-L1_A,0}}, 1);

  build->bg = Create_Background((L1_TOTAL-L1_A/2)*2,(L1_TOTAL-L1_A/2)*2);
  build->bg->frame->position.i[0] = x;

}

void Set_Level_1_Surfaces_Build(grCamera2D* camera2D, grRendering_System2D* rs, phRB_System2D* rb_sys, Level_1_Surfaces_Build* build) {

  if (build->build_with_physics) {
    build->rope->rc->rb_sys = rb_sys;
    build->rope->rc->camera2D = camera2D;
  }

  dAppend_LL(grRenderer_ptr)(build->bg->renderer, rs->_renderers);

  dAppend_LL(grRenderer_ptr)(build->portal->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->gem->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->player->renderer, rs->_renderers);
  if (build->build_with_physics) {
    dAppend_LL(grRenderer_ptr)(build->rope->renderer, rs->_renderers);
  }

  dAppend_LL(grRenderer_ptr)(build->hs1->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs2->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs3->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs4->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs5->renderer, rs->_renderers);
  dAppend_LL(grRenderer_ptr)(build->hs6->renderer, rs->_renderers);

  if (build->build_with_physics) {

    phAdd_Rigid_Body2D(build->player->rb, rb_sys);

    phAdd_Rigid_Body2D(build->hs1->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs2->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs3->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs4->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs5->rb, rb_sys);
    phAdd_Rigid_Body2D(build->hs6->rb, rb_sys);

    phAdd_Rigid_Body2D(build->gem->rb, rb_sys);

    phAdd_Rigid_Body2D(build->portal->rb, rb_sys);

    if (build->build_with_physics) {
      phAdd_Joint2D(&build->rope->rod_j->_super, rb_sys);
      phAdd_Joint2D(&build->rope->spring_j->_super, rb_sys);
    }

  }

}

void Add_Entities_Level_1_Surfaces_Build(geScene* scene, Level_1_Surfaces_Build* build) {

  geAdd_Entity(build->bg->_super, scene);

  geAdd_Entity(build->portal->_super, scene);

  geAdd_Entity(build->gem->_super, scene);

  geAdd_Entity(build->player->_super, scene);
  if (build->build_with_physics) {
    geAdd_Entity(build->rope->_super, scene);
  }

  geAdd_Entity(build->hs1->_super, scene);
  geAdd_Entity(build->hs2->_super, scene);
  geAdd_Entity(build->hs3->_super, scene);
  geAdd_Entity(build->hs4->_super, scene);
  geAdd_Entity(build->hs5->_super, scene);
  geAdd_Entity(build->hs6->_super, scene);

}
