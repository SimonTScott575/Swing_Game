#include <stdio.h>

#include <Game_Engine/Game_Engine.h>

#include "Scenes/Main_Menu.h"
#include "Scenes/Level_Select_Menu.h"
#include "Scenes/Level_1.h"
#include "Scenes/Level_2.h"
#include "Scenes.h"

#define GE_DEBUG_MODE 

int main() {

  // ######################
  // Library Initialization
  // ######################

  geInit();

  // #########
  // Load Game
  // #########

  geWindow* window = geCreate_Window(1200,1200,"Swing");
  geGame* game = geCreate_Game(window);

  Init_Scenes();

  main_menu = geCreate_Scene(Load_Main_Menu);
  geAdd_Scene(main_menu, game);

  level_select_menu = geCreate_Scene(Load_Level_Select_Menu);
  geAdd_Scene(level_select_menu, game);

  level_1 = geCreate_Scene(Load_Scene_1);
  geAdd_Scene(level_1, game);

  level_2 = geCreate_Scene(Load_Level_2);
  geAdd_Scene(level_2, game);

  level_order[0] = level_1;
  level_order[1] = level_2;

  grInit(); //!!!TODO: put this somewhere better, currently needed here for window's screen models needing an OpenGL context (I think)

  // #########
  // Game Loop
  // #########

  gePlay_Game(game);

  // ########
  // Clean Up
  // ########

  Terminate_Scenes();

  geDestroy_Game(game);

  geTerminate();

  // ###
  // Fin
  // ###

  printf("\nDEBUG : ENDING GAME SUCCESSFULLY\n");

  return 0;

}
