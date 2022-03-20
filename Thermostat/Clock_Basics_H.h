#include <EEPROM.h>

#include <LiquidCrystal.h>
#include "Encoder_Value_H.h"
#include "Button_Press_H.h"

#ifndef Clock_Basics_H.h
#define Clock_Basics_H.h

LiquidCrystal LcdDriver(A5, A4, 5, 6, 7, 8 );



// Variable used as clock settings.
int Hours, Minutes, Seconds;

float TempDay = EEPROM.get(0,TempDay);
//int eeAddress = sizeof(TempDay);
float TempNight = EEPROM.get(sizeof(TempDay),TempNight);
//float TempDay = 0;
//float TempNight = 0;


// This function is to be called every second
// to update the clock represented by the
// global variables Hours, Minutes, Seconds


void UpdateClock()
{
  // Check if Seconds not at wrap point.
  if (Seconds < 59)
  {
    Seconds++; // Move seconds ahead.
  }
  else
  {
    Seconds = 0; // Reset Seconds
    // and check Minutes for wrap.
    if (Minutes < 59)
    {
      Minutes++; // Move seconds ahead.
    }
    else
    {
      Minutes = 0; // Reset Minutes
      // check Hours for wrap
      if (Hours < 23)
      {
        Hours++;// Move Hours ahead.
      }
      else
      {
        Hours = 0;// Reset Hours
      }// End of Hours test.
    } // End of Minutes test
  } // End of Seconds test
} // end of UpdateClock()

// Send Hours, Minutes and Seconds to a display.
void SendClock()
{
  // Check if leading zero needs to be sent
  if (Hours < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Hours); // Then send hours
  LcdDriver.print(":"); // And separator
  // Check for leading zero on Minutes.
  if (Minutes < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Minutes); // Then send Minutes
  LcdDriver.print(":"); // And separator
  // Check for leading zero needed for Seconds.
  if (Seconds < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Seconds);
  LcdDriver.setCursor(9,0);
  LcdDriver.print("D ");
  LcdDriver.print(TempDay);
  LcdDriver.setCursor(9,1);
  LcdDriver.print("N ");
  LcdDriver.print(TempNight);// Then send Seconds
} // End of SendClock()

// States for setting clock.
enum ClockStates { CLOCK_RUNNING, CLOCK_SET_HOURS,
                   CLOCK_SET_MINUTES, CLOCK_SET_SECONDS, TEMP_SET_DAY, TEMP_SET_NIGHT };
ClockStates clockState = CLOCK_RUNNING;

// Function that processes incoming characters to set the clock.
void SettingClock(int Button, float UpDown )
{
  // interpret input based on state
  switch (clockState)
  {
  case CLOCK_RUNNING:
    if (Button){
      clockState = CLOCK_SET_HOURS;
      Hours = 0;   // Reset clock values.
      Minutes = 0;
      Seconds = 0;
    }
    break;
  case CLOCK_SET_HOURS: // 
    if (Button){
      clockState = CLOCK_SET_MINUTES;}
    else 
    {
      Hours += UpDown;
      if( Hours > 23 )
          Hours = 0;
      if( Hours < 0 )
          Hours = 23;
    } 
    break;
  case CLOCK_SET_MINUTES: // 
    if (Button){
      clockState = CLOCK_SET_SECONDS;}
    else
    {
      // eeAddress = 0;
      Minutes += UpDown; 
      if( Minutes > 59 )
          Minutes = 0;
      if( Minutes < 0 )
          Minutes = 59;
    } 
    break;
  case CLOCK_SET_SECONDS: // 
    if (Button){
      clockState = TEMP_SET_DAY;}
    else
    {
      Seconds += UpDown; 
      if( Seconds > 59 )
          Seconds = 0;
      if( Seconds < 0 )
          Seconds = 59;
      
    }
    break;
   
   case TEMP_SET_DAY: // 
    if (Button){
      clockState = TEMP_SET_NIGHT;}
    else 
    {
      TempDay += UpDown/2;
//      if( TempDay > 100 )
//          TempDay = 75;
//      if( TempDay < 0 )
//          TempDay = 75;
         }
          EEPROM.put(0, TempDay);
          //eeAddress = sizeof(float);
          break; 
    
    case TEMP_SET_NIGHT: // 
    if (Button){
      clockState = CLOCK_RUNNING;}
    else 
    {
      TempNight += UpDown/2;
//      if( TempNight > 100 )
//          TempNight = 75;
//      if( TempNight < 0 )
//          TempNight = 75;
       EEPROM.put(sizeof(TempDay), TempNight);
       //eeAddress = sizeof(float);   
    }
      break;
    }
   

  }// End of clock mode switch.

 // End of SettingClock

#endif
