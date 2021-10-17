#include "Score_Counter.h"

#include <stdio.h>

#include "Gem_Controller.h"

void Score_Counter_ctor(Score_Counter* self, grText* text_num, grText* text_den) {

  *self = (Score_Counter){

    .text_num = text_num,
    .text_den = text_den

  };

  Set_Score_Text(text_num, text_den);

  geComponent_ctor(&self->_super);
  geSet_Sub_Component(self, Update_Score_Counter, NULL, &self->_super);

}

void Set_Score_Text(grText* text_num, grText* text_den) {

  char s[100];

  sprintf(s, "%d", g_gems_caught_count);
  grSet_Text_Contents(s, text_num);

  s[0] = '/';
  sprintf(s+1, "%d", g_gems_count);
  grSet_Text_Contents(s, text_den);

}

void Update_Score_Counter(geComponent* component) {

  Score_Counter* counter = component->_sub;

  Set_Score_Text(counter->text_num, counter->text_den);

}
