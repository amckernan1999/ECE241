#include <LiquidCrystal.h>
LiquidCrystal Lcd(A5, A4, 5, 6, 7, 8 );

int ButtonState;
unsigned long ButtonTime;
int input;

unsigned long timer;

int encoderPosition = 0;

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

void setup() {
ButtonState = 0;
Lcd.begin(2,16);
Lcd.clear();
timer = millis();
attachInterrupt(0,MonitorA,CHANGE);
attachInterrupt(1,MonitorB,CHANGE);

}

void loop() {
if( ButtonNextState( digitalRead(4))){
  encoderPosition--;
}
if( millis() - timer >= 100){
Lcd.clear();
Lcd.print(encoderPosition);
timer += 100;
}
}
