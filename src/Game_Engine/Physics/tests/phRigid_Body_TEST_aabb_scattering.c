#include "../phCollision_Solver.h"

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

  mFrame2D frame1 = init_mFrame2D(mMul_f_V2f( 1,mVector2f_X), 0, mMul_f_V2f(0.2, mVector2f_ONE));
  mFrame2D frame2 = init_mFrame2D(mMul_f_V2f(-1,mVector2f_X), 0, mMul_f_V2f(0.2, mVector2f_ONE));

  frame1.position = mAdd_V2f(frame1.position, mMul_f_V2f(0.05f, mVector2f_Y));
  frame2.position = mAdd_V2f(frame2.position, mMul_f_V2f(-0.05f, mVector2f_Y));

  float vertices1[8] = {0.5,0.5, -0.5,0.5, -0.5,-0.5, 0.5,-0.5};
  // float vertices2[10] = {
  //   -0.5,-0.5,
  //   0.5,-0.5,
  //   1,0,
  //   0.5,0.5,
  //   -0.5,0.5
  // };
  phCollider2D* collider1 = new_phCollider2D_AABB(&frame1, NULL, NULL, 1, 1); // new_phCollider2D_POLYGON(&frame1, vertices1, 4);
  phCollider2D* collider2 = new_phCollider2D_AABB(&frame2, NULL, NULL, 1, 1);

  phRigid_Body2D rb1 = init_phRigid_Body2D(&frame1, 1, 10/12.0f*(0.2*0.2*2), collider1);
  rb1.velocity = mMul_f_V2f( -0.25f, mVector2f_X);
  // rb1.angular_velocity = 0;
  rb1.is_static_rotation = true;
  phRigid_Body2D rb2 = init_phRigid_Body2D(&frame2, 1, 1/2.0*0.1*0.1, collider2);
  rb2.velocity = mMul_f_V2f(  0.25f, mVector2f_X);
  // rb2.angular_velocity = 0;
  rb2.is_static_rotation = true;

  rb1.restitution = 1;
  rb2.restitution = 1;

  phCollision2D collisions[100];

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

  // ====
  // Loop
  // ====

  bool has_collided = false;

  double last_time = sysTime();
  while (!sysApplicationShouldClose()) {

    float background_colour[4] = {1,1,1,1};

    if ( sysTime() - last_time > phDELTA_T ) {

      // ------
      // Update
      // ------

      uint64_t n_collisions = phDetect_Collisions(&rb1, &rb2, collisions);
      if (n_collisions > 0){// && !has_collided) {
        background_colour[1] = background_colour[2] = 0;

        printf("%f %f\n", collisions[0].position.i[0], collisions[0].position.i[1]);

        mVector2f collision_force = phGet_Collision_Force(collisions[0], rb1, rb2);
        rb1.force = collision_force;
        rb2.force = mMul_f_V2f(-1,collision_force);

        has_collided = true;
      }

      phApply_Rigid_Body_Force(&rb1);
      phApply_Rigid_Body_Force(&rb2);

      // reset forces
      rb1.force = mVector2f_ZERO;
      rb2.force = mVector2f_ZERO;
      rb1.torque = 0;
      rb2.torque = 0;

      // ----
      // Draw
      // ----

      grSet_Clear_Screen_Colour( background_colour , grDEFAULT_SCREEN  );
      grClear_Screen_Colour(grDEFAULT_SCREEN);

      grRender(renderer);
      grRender(renderer2);

      glfwSwapBuffers( (GLFWwindow*) app->window );
      sysPoll_Events();

      last_time = sysTime();
    }
  }

  sysTerminate();

  printf("\nPROGRAM ENDING SUCCESSFULLY\n");
}
