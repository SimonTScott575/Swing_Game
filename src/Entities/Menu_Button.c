#include "Menu_Button.h"

#include "../Scenes.h"

Menu_Button* Create_Menu_Button(float x, float y, float x_offset, float y_offset, float width, float height, char* texture_path, geOn_Click_fn on_click) {

  geEntity* entity = geCreate_Entity();

  mFrame2D* frame = new_mFrame2D((mVector2f){{x_offset,y_offset}}, 0, (mVector2f){{1,1}}); //? scale ?

  grSprite* sprite = grCreate_Sprite(texture_path, width, height);

  geButton_UI* button_ui = geCreate_Button_UI(width, height, frame);
  button_ui->_super.x = x;
  button_ui->_super.y = y;
  button_ui->on_click = on_click;

  geUI_Renderer* ui_r = grCreate_UI_Renderer(&button_ui->_super, sprite->_model, sprite->_shader);

  geAdd_Component(frame->_super, entity);
  geAdd_Component(ui_r->_super->_super, entity);
  geAdd_Component(button_ui->_super._super, entity);

  Menu_Button* menu_b = malloc(sizeof(Menu_Button)); //??? how is sub destroyed ???
  *menu_b = (Menu_Button){
    ._super = entity,
    .frame = frame,
    .sprite = sprite,
    .ui_r = ui_r,
    .button_ui = button_ui
  };

  geSet_Sub_Entity(menu_b, Destroy_Menu_Button_Sub_Entity, entity);

  return menu_b;

}

void Destroy_Menu_Button_Sub_Entity(geEntity* entity) {

  Menu_Button* menu_b = entity->_sub;

  grDestroy_Sprite(menu_b->sprite);

  free(menu_b);

}
