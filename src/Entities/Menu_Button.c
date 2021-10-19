#include "Menu_Button.h"

#include "../Scenes.h"

Menu_Button* Create_Menu_Button(
  float x, float y,
  float x_offset, float y_offset,
  float width, float height,
  char* texture_path,
  geOn_Click_fn on_click,
  geScene* scene
) {

  Menu_Button* menu_b = malloc(sizeof(Menu_Button)); //??? how is sub destroyed ???
  if (menu_b == NULL) { return NULL; }

  geEntity_ctor(&menu_b->_super);
  geSet_Sub_Entity(menu_b, Destroy_Menu_Button_Sub_Entity, &menu_b->_super);

  menu_b->frame = mFrame2D_init((mVector2f){{x_offset,y_offset}}, 0, (mVector2f){{1,1}}); //? scale ?

  menu_b->sprite = grCreate_Sprite(texture_path, width, height);
  if (menu_b->sprite == NULL) {
    free(menu_b);
    return NULL;
  }

  geButton_UI_ctor(&menu_b->button_ui, width, height, &menu_b->frame);
  menu_b->button_ui._super.x = x;
  menu_b->button_ui._super.y = y;
  menu_b->button_ui.on_click = on_click;

  menu_b->ui_r = grCreate_UI_Renderer(&menu_b->button_ui._super,
                                      &menu_b->sprite->_model,
                                      &menu_b->sprite->_shader);

  geAdd_Component(&menu_b->ui_r->_super._super, &menu_b->_super);
  geAdd_Component(&menu_b->button_ui._super._super, &menu_b->_super);

  geAdd_Entity(&menu_b->_super, scene);

  return menu_b;

}

void Destroy_Menu_Button_Sub_Entity(geEntity* entity) {

  Menu_Button* menu_b = entity->_sub;

  grDestroy_Sprite(menu_b->sprite);

  free(menu_b);

}
