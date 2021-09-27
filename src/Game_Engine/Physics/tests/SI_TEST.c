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

  // ========
  // Graphics
  // ========

  grInit(800, 800); //? must be after create sys app ?

  grMesh* mesh = grCreate_Mesh("../../Graphics/Meshes/grRect2D.obj");
  grModel* model = grCreate_Model(&mesh, 1);
  grDestroy_Mesh(mesh);

  grShader* shader = grCreate_Shader("../../Graphics/Shaders/grTex_2D_vert.glsl", "../../Graphics/Shaders/grTex_2D_frag.glsl");
  grTexture* texture = grCreate_Texture("../../Graphics/tests/container.jpg");
  grSet_Texture_by_name("grTexture", texture, shader);

  grRenderer* renderer = grCreate_Renderer(&frame1, model, shader, grRender_2D);
  grRenderer* renderer2 = grCreate_Renderer(&frame2, model, shader, grRender_2D);

  // ====
  // Loop
  // ====

  bool has_collided = false;

  int a = 0;
  double last_time = sysTime();
  while (!sysApplicationShouldClose()) {

    float background_colour[4] = {1,1,1,1};

    if ( sysTime() - last_time > 0.02f ) {

      // ------
      // Update
      // ------



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
