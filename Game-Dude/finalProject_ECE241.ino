
////////////////////////
//VARIABLE DECLARATION//
#define INTERVAL 500  //Time Interval
unsigned long Timer;  //Timer value
int button, encoder, button_flag;  //Control variables
int GameSelected = 1; // Curent Game Selected


/////////////////////////
// IMPORTS HEADER FILES//
#include "Screen.h"
#include "Controls.h"
#include "Hi_Score.h"
#include "Game_1.h"
#include "Game_2.h"


////////////////////
//GAME MODE SELECT//
void GameMode( int buttonPress, int UpDown ) // Implements Game with Controls
{
  if ( GameSelected == 1 )  // If Game1 is Selected
  {
    if ( buttonPress < 2 )        // If Button is idle or short press
      _g1_Frame( buttonPress, UpDown ); // Call Next Frame Function
    else if ( buttonPress == 2 )  // IF Button is medium press
    {
      lives = -1;
      _g1_Frame( buttonPress, UpDown);           // Re-initialize game
    }
    else                          // If Button is long press
    {
      GameSelected = 2;             // Switch Game Selected
      _g2_Timer = 0;
      _g2_Init();                   // Initialize Game2
    }
  } // End of Game1 State
  
  else                      // If Game2 is Selected
  {
    if ( buttonPress < 2 )        // If Button is idle or short press
      _g2_Frame( buttonPress, UpDown ); // Call Next Frame Function
    else if ( buttonPress == 2 )  // IF Button is medium press
      {_g2_Win_Flag = 0;
      _g2_Timer = 0;
      _g2_Init();}                       // Re-initialize game
    else                          // If Button is long press
    {
      GameSelected = 1;             // Switch Game Selected
      _g1_Init();                   // Initialize Game1
    }
  } // End of Game2 State
  
}// End of GameMode Function



////////////////////////
//SETUP/INITIALIZATION//
void setup() 
{
  Timer = millis();   //Sets Timer to millis()
  _init_Controls();   //Initializes Controls
  _init_Screen();     //Initializes Screen
  _g1_Init();
  internal_Hi_Score();
}

////////////
//LOOP/RUN//
void loop() 
{ //Main Interval Loop

  button_flag = Button();
  if( button_flag != 0 )
    button = button_flag;
  
  if ( millis() - Timer >= INTERVAL - time_modifier ) 
  { 
    Timer = millis();
    encoder = EncoderDetent();  //Detects encoder position
    
    GameMode( button, encoder );
    button = 0;
  }  
}
