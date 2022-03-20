#include <EEPROM.h>
#include <LiquidCrystal.h>

#include "Clock_Basics_H.h"
#include "Button_Press_H.h"
#include "Encoder_Value_H.h"
#include "SPI_H.h"

unsigned long UpdateTimer;
unsigned long ClockTimer;
unsigned long SendTimer;
unsigned long SetTimer;
unsigned long TempTimer;
float tempF; 
float tempC;
float tempA;

int flag;
int EncoderTracking;

void setup() {
  
  
  ClockTimer = millis();
  UpdateTimer = millis();
  SendTimer = millis();
  TempTimer = millis();
  SW_SPI_Initialize();
  ClockStates clockState = CLOCK_RUNNING;

  attachInterrupt(0,MonitorA,CHANGE);
  attachInterrupt(1,MonitorB,CHANGE);
  
  LcdDriver.begin(2,16);
  SendClock();
  ButtonState = 0;
  Serial.begin(9600);

  EncoderTracking = encoderPosition;
  }

void loop() {

  if(millis() - SetTimer >= 300){
    SetTimer = millis();}
  
  
  if(ButtonNextState(0) == 1){
  SettingClock(1,0); 
  //SettingTemp(1,0); 
  } // So update state.
  else if ((encoderPosition - EncoderTracking) >= 4){
    SettingClock( 0,1);  // Indicate positive travel
    //SettingTemp( 0,-1);
    EncoderTracking += 4;   // and move tracking variable.
  }
  else if ((encoderPosition - EncoderTracking) <= -4){
    SettingClock( 0,-1);  // Indicate negative travel
    //SettingTemp( 0,+1);
    EncoderTracking -= 4;
  }


  
 
  if(millis() - SendTimer >= 300){
    LcdDriver.clear();
    SendClock();
      int TempBits = ( SW_SPI() >> 3 ) & 0x0fff;
    float tempC = 0.25 * (float)TempBits;
    float tempF = 1.8 * tempC + 32.0;
    LcdDriver.setCursor(0,1);
    LcdDriver.print("Tmp");
    LcdDriver.print(tempF);//REPLACE WITH 'tempF' AFTER TESTING
    tempA =  75;
    SendTimer = millis();
  }
if(millis() - UpdateTimer >=1000){
 if(clockState == CLOCK_RUNNING){
  UpdateClock();}
 // Serial.print(TempDay);
  //Serial.print(TempDay);
 UpdateTimer = millis();
}

if(millis() - TempTimer >=1000){
  if(Hours >= 7 and Hours <21){
    
    if(tempA >= TempDay + 5){
      digitalWrite(A3, HIGH);
      flag =  1;
      Serial.print("\ncooling day");}
        
    if(tempA <= TempDay - 5){
      digitalWrite(A1, HIGH);
      flag = 2;
      Serial.print("\nheating day");}
    
   
    if(tempA <= TempDay and flag == 1){
        flag = 0;
        digitalWrite(A3, LOW);
        Serial.print("\nday cool end");}

    if(tempA >= TempDay and flag == 2){
        flag = 0;
        digitalWrite(A1, LOW);
        Serial.print("\nday heat end");}
    }   
  
  
  if(Hours < 7 or Hours >= 21){
   
    if(tempA >= TempNight + 5){
      digitalWrite(A3, HIGH);
      flag = 3;
      Serial.print("\ncooling night");}
      
      
    if(tempA <= TempNight - 5){
      digitalWrite(A1, HIGH);
      flag = 4;
      Serial.print("\nheating night");}
      
    
   if(tempA <= TempNight and flag == 3){
        flag = 0;
        digitalWrite(A3, LOW);
        Serial.print("\nnightcool end");}

    if(tempA >= TempNight and flag == 4){
        flag = 0;
        digitalWrite(A1, LOW);
        Serial.print("\nnight heat end");}
  }
     
    
   
    TempTimer = millis();
  
  }
}
