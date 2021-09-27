#include "../phRB_System.h"

#include <stdio.h>
#include <stdbool.h>

#include <Game_Engine/include/glad/glad.h>
#include <Game_Engine/include/GLFW/glfw3.h>

#include <Game_Engine/System/System.h>
#include <Game_Engine/Graphics/Graphics.h>

#include <Game_Engine/Maths/mVector.h>

int main() {

  // ======
  // System
  // ======

  sysInit();

  sysApplication* app = sysCreate_Application(800, 800, "TEST");
  sysSet_Active_Application(app);

  // =======
  // Physics
  // =======

  mFrame2D frames[50];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j <10; j++) {
      frames[i*10 + j] = init_mFrame2D((mVector2f){{-1 + 2*j/10.0f + i/15.0f, i/5.0f}}, 0, mMul_f_V2f(0.1, mVector2f_ONE));
    }
  }
  mFrame2D frame1 = init_mFrame2D(mMul_f_V2f(-1, mVector2f_Y), 0, mMul_f_V2f(1, mVector2f_ONE));

  float vertices[8] = {0.5,0.5, -0.5,0.5, -0.5,-0.5, 0.5,-0.5};
  phCollider2D* colliders[50];
  for (int i = 0; i < 50; i++) {
    colliders[i] = new_phCollider2D_AABB(&frames[i], NULL, NULL, 1, 1);
  }
  phCollider2D* collider1 = new_phCollider2D_AABB(&frame1, NULL, NULL, 1, 1);

  phRigid_Body2D rbs[50];
  for (int i = 0; i < 50; i++) {
    rbs[i] = init_phRigid_Body2D(&frames[i], 1, 1/12.0f*(0.2*0.2*2), colliders[i]);
    rbs[i].restitution = 0.5;
    rbs[i].is_static_rotation = true;
  }
  phRigid_Body2D rb1 = init_phRigid_Body2D(&frame1, 1, 1/12.0f*(0.2*0.2*2), collider1);
  rb1.is_kinetic = false;
  rb1.is_static = true; //??? see what happens take away is static !!!
  rb1.is_static_rotation = true;
  rb1.restitution = 0.5;

  phRB_System2D* rb_sys = new_phRB_System2D();
  for (int i = 0; i < 50; i++) {
    phAdd_Rigid_Body(&rbs[i], rb_sys);
  }
  phAdd_Rigid_Body(&rb1, rb_sys);

  rb_sys->global_force = (mVector2f){{0,-0.5}};

  // ========
  // Graphics
  // ========

  grInit(800, 800); //? must be after create sys app ?

  grMesh* mesh = grCreate_Mesh("../Graphics/Meshes/grRect2D.obj");
  grModel* model = grCreate_Model(&mesh, 1);
  grDestroy_Mesh(mesh);

  grShader* shader = grCreate_Shader("../Graphics/Shaders/grTex_2D_vert.glsl", "../Graphics/Shaders/grTex_2D_frag.glsl");
  grTexture* texture = grCreate_Texture("../Graphics/tests/container.jpg");
  grSet_Texture_by_name("grTexture", texture, shader);

  grRenderer* renderers[50];
  for (int i = 0; i < 50; i++) {
    renderers[i] = grCreate_Renderer(&frames[i], model, shader, grRender_2D);
  }
  grRenderer* renderer = grCreate_Renderer(&frame1, model, shader, grRender_2D);

  // ====
  // Loop
  // ====

  bool has_collided = false;

  int a = 0;
  double last_time = sysTime();
  while (!sysApplicationShouldClose()) {

    float background_colour[4] = {1,1,1,1};

    if ( sysTime() - last_time > phDELTA_T ) {

      // ----
      // Draw
      // ----

      grSet_Clear_Screen_Colour( background_colour , grDEFAULT_SCREEN  );
      grClear_Screen_Colour(grDEFAULT_SCREEN);


      grRender(renderer);
      for (int i = 0; i < 50; i++) {
        grRender(renderers[i]);
      }

      // ------
      // Update
      // ------

      phAdd_Globals_RB_System2D(rb_sys);
      phUpdate_RB_System2D(rb_sys);
      phZero_RB_System2D(rb_sys);

      glfwSwapBuffers( (GLFWwindow*) app->window );
      sysPoll_Events();

      last_time = sysTime();
    }
  }

  sysTerminate();

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");
}
