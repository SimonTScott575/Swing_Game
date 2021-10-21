#include "Resource_Manager.h"

grFont* g_main_font = NULL;

void Init_Resource_Manager() {

  g_main_font = grCreate_Font(MAIN_FONT_PATH, MAIN_FONT_RES);

}

void Terminate_Resource_Manager() {

  grDestroy_Font(g_main_font);

}
