#include "Score_Counter.h"

#include <stdio.h>

#include "Gem_Controller.h"

Score_Counter* Create_Score_Counter(grText* text_num, grText* text_den) {

  Set_Score_Text(text_num, text_den);

  Score_Counter* counter = malloc(sizeof(Score_Counter));
  *counter = (Score_Counter){

    .text_num = text_num,
    .text_den = text_den

  };

  counter->_super = geCreate_Component();
  geSet_Sub_Component(counter, Update_Score_Counter, Destroy_Score_Counter_Sub_Component, counter->_super);

  return counter;

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

void Destroy_Score_Counter_Sub_Component(geComponent* component) {

  Score_Counter* counter = component->_sub;

  free(counter);

}
