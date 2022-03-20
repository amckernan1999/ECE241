
#ifndef Encoder_Value_H.h
#define Encoder_Value_H.h


unsigned long timer;

int encoderPosition = 0;

void MonitorA(){
if(digitalRead(2) == digitalRead(3)){
encoderPosition++;}
else{
encoderPosition--;}
}

void MonitorB(){
if(digitalRead(2) == digitalRead(3)){
encoderPosition--;}
else{
encoderPosition++;}
}

void MonitorC(){
  if(digitalRead(4)== LOW){
    encoderPosition--;
  }  
}


#endif
