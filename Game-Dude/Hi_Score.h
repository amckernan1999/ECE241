#ifndef Hi_Score_H
#define Hi_Score_H

#include <EEPROM.h>         //EEPROM

int _g1_Hi_Score, _g2_Hi_Score;

void new_Hi_Score(int new_score, int game)  //function checks what game mode we are currently in
{
  if( game == 1 )
  {
    _g1_Hi_Score = new_score;
    EEPROM.put(0, _g1_Hi_Score);  //stores highscore
  }
  else
  {
    _g2_Hi_Score = new_score;
    EEPROM.put(64, _g2_Hi_Score); //stores highscore
  }
  
}

void internal_Hi_Score()
{
  _g1_Hi_Score = EEPROM.get(0, _g1_Hi_Score); //reads highscore
  _g2_Hi_Score = EEPROM.get(64, _g2_Hi_Score);  //reads highscore
}

#endif 
