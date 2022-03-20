#ifndef Button_Press_H.h
#define Button_Press_H.h

int ButtonState;
unsigned long ButtonTime;
int input;


int ButtonNextState( int input){

switch(ButtonState){
  case 0: //IDLE
  if(digitalRead(4) ==LOW){
  ButtonTime = millis();
  ButtonState = 1;
  break;
  }
case 1: //WAIT
if(digitalRead(4) == HIGH){
ButtonState = 0;
break;
}
else if( millis() - ButtonTime >= 5){
ButtonState = 2;
return 1;
break;
}
case 2: //LOW
if(digitalRead(4) == HIGH){
ButtonState = 0;
}
}
return 0;
}





#endif
