#ifndef SCORE_COUNTER_H
#define SCORE_COUNTER_H

#include <Game_Engine/Game_Engine.h>

typedef
struct Score_Counter {

  geComponent* _super;

  // mFrame2D* frame_num;
  // mFrame2D* frame_den;
  //
  // grFont* font;
  grText* text_num;
  grText* text_den;

  // grShader* shader;
  // grText_Renderer* text_r_num;
  // grText_Renderer* text_r_den;


} Score_Counter;

Score_Counter* Create_Score_Counter(grText* text_num, grText* text_den);
void Destroy_Score_Counter_Sub_Component(geComponent* component);

void Update_Score_Counter(geComponent* component);

void Set_Score_Text(grText* text_num, grText* text_den);

#endif
