#include "../phRigid_Body.h"

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

  float vertices[8] = {0.5,0.5, -0.5,0.5, -0.5,-0.5, 0.5,-0.5};
  phCollider2D* collider1 = new_phCollider2D_POLYGON(&frame1, vertices, 4); // new_phCollider2D_POLYGON(&frame1, vertices1, 4);
  phCollider2D* collider2 = new_phCollider2D_POLYGON(&frame2, vertices, 4);

  phRigid_Body2D rb1 = init_phRigid_Body2D(&frame1, 1, 1/12.0f*0.2*0.2*2, collider1);
  rb1.velocity = mMul_f_V2f( -0.25f, mVector2f_X);
  // rb1.angular_velocity = 0;
  phRigid_Body2D rb2 = init_phRigid_Body2D(&frame2, 1, 1/12.0*0.2*0.2*2, collider2);
  rb2.velocity = mMul_f_V2f(  0.25f, mVector2f_X);
  // rb2.angular_velocity = 3.14;

  rb1.restitution = 1;
  rb2.restitution = 1;

  phCollision2D collisions[100] = {0};

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

    if ( sysTime() - last_time > phDELTA_T ) { //T

      // ------
      // Update
      // ------

      // mGenerate_transform_2D(&frame1);
      // mGenerate_transform_2D(&frame2);

      uint64_t n_collisions = phDetect_Collision(collider1, collider2, collisions);

      //
      float d_dot[100]; //?

      if (n_collisions > 0) {
        background_colour[1] = background_colour[2] = 0;

        int n_iterations = (n_collisions == 1) ? 1 : 1;
        for (int nth_iteration = 0; nth_iteration < n_iterations; nth_iteration++) {

          for (uint64_t n = 0; n < n_collisions; n++) {

            if (nth_iteration == 0) { //?
              mVector2f r1 = mSub_V2f(collisions[n].position, rb1.frame->position);
              mVector2f r2 = mSub_V2f(collisions[n].position, rb2.frame->position);
              float r1_cross_n = r1.i[0]*collisions[n].normal.i[1] - r1.i[1]*collisions[n].normal.i[0];
              float r2_cross_n = r2.i[0]*collisions[n].normal.i[1] - r2.i[1]*collisions[n].normal.i[0];
              mVector2f rel_vel = mSub_V2f(rb1.velocity, rb2.velocity);

              d_dot[n] = mDot_V2f( rel_vel, collisions[n].normal )
                + rb1.angular_velocity*r1_cross_n
                - rb2.angular_velocity*r2_cross_n;
            }
            // if (d_dot[n] >= 0) { //?
            //   printf("continue\n");
            //   continue;
            // }

            // mVector2f collision_force = phGet_Collision_Force(collisions[n], rb1, rb2);
            float lambda = phGet_Collision_Lambda(collisions[n], rb1, rb2);

            printf("%f\n", lambda);

            // Clamp //!!!
            float temp_accum_lambda = collisions[n].accum_lambda;
            collisions[n].accum_lambda = fmax(collisions[n].accum_lambda + lambda, 0);
            lambda = collisions[n].accum_lambda - temp_accum_lambda;

            mVector2f collision_force = mMul_f_V2f(lambda, collisions[n].normal);

            printf("%f %f %f\n", lambda, collisions[n].normal.i[0], collisions[n].normal.i[1]);

            // Set impulse
            phSet_Force( collision_force, collisions[n].position, &rb1 );
            phSet_Force( mMul_f_V2f(-1, collision_force), collisions[n].position, &rb2 );
            // phSet_Force(mAdd_V2f( rb1.force , collision_force ), collisions[n].position, &rb1);
            // phSet_Force(mAdd_V2f( rb2.force , mMul_f_V2f(-1, collision_force) ), collisions[n].position, &rb2);

            // update velocity
            phApply_Force_On_Velocity(&rb1);
            phApply_Force_On_Velocity(&rb2);

            if (nth_iteration == n_iterations - 1) {
              printf("clear\n");
              collisions[n].accum_lambda = 0;
            }

          }

        }
        printf("\n");

        has_collided = true;
      }

      phApply_Velocity_On_Position(&rb1);
      phApply_Velocity_On_Position(&rb2);
      // phApply_Rigid_Body_Force(&rb1);
      // phApply_Rigid_Body_Force(&rb2);

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
