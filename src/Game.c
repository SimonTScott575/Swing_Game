#include <stdio.h>

#include <Game_Engine/Game_Engine.h>

#include "Scenes/Main_Menu.h"
#include "Scenes/Level_Select_Menu.h"
#include "Scenes/Level_1.h"
#include "Scenes/Level_2.h"
#include "Scenes/Level_3.h"
#include "Scenes/Level_4.h"
#include "Scenes/Level_5.h"
#include "Scenes.h"
#include "Glow.h"

#include "Scenes/Level_Builder.h"

int main() {

  // ######################
  // Library Initialization
  // ######################

  geInit();

  // #########
  // Load Game
  // #########

  geWindow* window = geCreate_Window(1200,1200,"Swing"); //TODO: start fullscreen (windowed?)
  grInit(); //!!!TODO: put this somewhere better, currently needed here for window's screen models needing an OpenGL context (I think)

  geGame* game = geCreate_Game(window);

  Init_Scenes();

  main_menu = geCreate_Scene(Load_Main_Menu);
  geAdd_Scene(main_menu, game);

  level_select_menu = geCreate_Scene(Load_Level_Select_Menu);
  geAdd_Scene(level_select_menu, game);

  level_1 = geCreate_Scene(Load_Level_1);
  geAdd_Scene(level_1, game);

  level_2 = geCreate_Scene(Load_Level_2);
  geAdd_Scene(level_2, game);

  level_3 = geCreate_Scene(Load_Level_3);
  geAdd_Scene(level_3, game);

  level_4 = geCreate_Scene(Load_Level_4);
  geAdd_Scene(level_4, game);

  level_5 = geCreate_Scene(Load_Level_5);
  geAdd_Scene(level_5, game);

  level_order[0] = level_1;
  level_order[1] = level_2;
  level_order[2] = level_3;
  level_order[3] = level_4;
  level_order[4] = level_5;

  Init_Glow_PP(1200,1200);

  // #########
  // Game Loop
  // #########

  gePlay_Game(game);

  // ########
  // Clean Up
  // ########

  //!!! destroy scenes from above !

  Terminate_Scenes();

  geDestroy_Game(game);
  geDestroy_Window(window);

  geTerminate();

  // ###
  // Fin
  // ###

  printf("\nDEBUG : ENDING GAME SUCCESSFULLY\n");

  return 0;

}
