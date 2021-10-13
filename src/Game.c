#include <stdio.h>

#include <Game_Engine/Game_Engine.h>

#include "Scenes/Main_Menu.h"
#include "Scenes/Level_Select_Menu.h"
#include "Scenes/Level_1.h"
#include "Scenes/Level_2.h"
#include "Scenes/Level_3.h"
#include "Scenes/Level_4.h"
#include "Scenes/Level_5.h"
#include "Scenes/Level_6.h"
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

  Import_Best_Times();

  g_main_menu = geCreate_Scene(Load_Main_Menu);
  geAdd_Scene(g_main_menu, game);

  g_level_select_menu = geCreate_Scene(Load_Level_Select_Menu);
  geAdd_Scene(g_level_select_menu, game);

  Init_Level_1_Spec();
  Init_Level_2_Spec();
  Init_Level_3_Spec();
  Init_Level_4_Spec();
  Init_Level_5_Spec();
  Init_Level_6_Spec();
  Accumulate_Specs();

  level_order[0] = geCreate_Scene(Load_Level_1);
  level_order[1] = geCreate_Scene(Load_Level_2);
  level_order[2] = geCreate_Scene(Load_Level_3);
  level_order[3] = geCreate_Scene(Load_Level_4);
  level_order[4] = geCreate_Scene(Load_Level_5);
  level_order[5] = geCreate_Scene(Load_Level_6);
  geAdd_Scene(level_order[0], game);
  geAdd_Scene(level_order[1], game);
  geAdd_Scene(level_order[2], game);
  geAdd_Scene(level_order[3], game);
  geAdd_Scene(level_order[4], game);
  geAdd_Scene(level_order[5], game);

  Init_Glow_PP(1200,1200);

  // #########
  // Game Loop
  // #########

  gePlay_Game(game);

  // ########
  // Clean Up
  // ########

  for (int i = 0; i < LEVELS_COUNT; i++) {
    geDestroy_Scene(level_order[i]);
  }
  Deport_Best_Times();

  geDestroy_Game(game);
  geDestroy_Window(window);

  geTerminate();

  // ###
  // Fin
  // ###

  printf("\nDEBUG : ENDING GAME SUCCESSFULLY\n");

  return 0;

}
