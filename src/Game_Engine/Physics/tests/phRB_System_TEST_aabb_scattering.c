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

  mFrame2D frame1 = init_mFrame2D(mVector2f_ZERO,             0, mMul_f_V2f(0.2, mVector2f_ONE));
  mFrame2D frame2 = init_mFrame2D(mMul_f_V2f(-1, mVector2f_Y), 0, mMul_f_V2f(0.4, mVector2f_ONE));
  mFrame2D frame3 = init_mFrame2D(mMul_f_V2f( 1, mVector2f_Y), 0, mMul_f_V2f(0.4, mVector2f_ONE));

  frame1.position = mAdd_V2f(frame1.position, mMul_f_V2f(0, mVector2f_Y));
  //frame2.position = mAdd_V2f(frame2.position, mMul_f_V2f(-0.05, mVector2f_Y));
  //frame3.position = mAdd_V2f(frame3.position, mMul_f_V2f(0.05, mVector2f_X));

  //float vertices1[8] = {0.5,0.5, -0.5,0.5, -0.5,-0.5, 0.5,-0.5};
  phCollider2D* collider1 = new_phCollider2D_AABB(&frame1, NULL, NULL, 1, 1);
  phCollider2D* collider2 = new_phCollider2D_AABB(&frame2, NULL, NULL, 1, 1);
  phCollider2D* collider3 = new_phCollider2D_AABB(&frame3, NULL, NULL, 1, 1);

  phRigid_Body2D rb1 = init_phRigid_Body2D(&frame1, 1, 1/12.0f*(0.2*0.2*2), collider1);
  //rb1.velocity = mMul_f_V2f( -0.5, mVector2f_X);
  //rb1.angular_velocity = 0;
  rb1.is_static = true;
  rb1.is_static_rotation = true;
  phRigid_Body2D rb2 = init_phRigid_Body2D(&frame2, 2, 2/12.0f*(0.2*0.2*2), collider2);
  rb2.velocity = mMul_f_V2f( 0.5, mVector2f_Y);
  //rb2.angular_velocity = 3;
  rb2.is_static_rotation = true;
  phRigid_Body2D rb3 = init_phRigid_Body2D(&frame3, 2, 2/12.0f*(0.2*0.2*2), collider3);
  rb3.velocity = mMul_f_V2f( -0.5, mVector2f_Y);
  //rb3.angular_velocity = 0;
  //rb3.is_kinetic = false;
  rb3.is_static_rotation = true;

  rb1.restitution = 1;
  rb2.restitution = 1;
  rb3.restitution = 1;

  phRB_System2D* rb_sys = new_phRB_System2D();
  phAdd_Rigid_Body(&rb1, rb_sys);
  phAdd_Rigid_Body(&rb2, rb_sys);
  phAdd_Rigid_Body(&rb3, rb_sys);

  //rb_sys->global_force = mMul_f_V2f(-0.2f, mVector2f_Y);

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

  grRenderer* renderer = grCreate_Renderer(&frame1, model, shader, grRender_2D);
  grRenderer* renderer2 = grCreate_Renderer(&frame2, model, shader, grRender_2D);
  grRenderer* renderer3 = grCreate_Renderer(&frame3, model, shader, grRender_2D);

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
      grRender(renderer2);
      grRender(renderer3);

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
