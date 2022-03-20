#ifndef Controls_H
#define Controls_H


////////////////////////
//VARIABLE DECLARATION//
  // Button Declarations
#define MEDIUM 1000            //Medium Interval
#define LONG 3000             //Long Interval
unsigned long ButtonTime;     //Button Timer
enum BState{ Idle, Wait,      //State Machine Variable Type Declaration
    Short, Medium, Long };
BState ButtonState = Idle;    //State machine varaible


  // Encoder Declarations
#define DETENT 4              //Detent Value
volatile int encoderValue = 0;//Direct Encoder Value
int EncoderTracking = 0;      //Detent Encoder Tracker



////////////////////
//BUTTON FUNCTIONS//
int ButtonNextState(int input)  //Button State Function
{ 
// ButtonState Switch Statement
  switch(ButtonState)
  {
//No Button Action
    case Idle: 
      if( input == LOW )  //If Button Pressed
      {
        ButtonTime = millis();  //Set Timer
        ButtonState = Wait;        //Wait/Debounce State
      }
    break;
// Debounces Button
    case Wait: 
      if( input == HIGH ) //If Button Released
        ButtonState = Idle;    //Idle State
      else if( millis() - ButtonTime >= 5 ) // If Bounce has passed
        ButtonState = Short;                  //Short State
      break;    
// Detects Short Button Hold
    case Short: 
      if( input == HIGH ) //If Button Released
      {
        ButtonState = Idle; //Idle State
        return 1;           //Return 1
      }
      else if ( millis() - ButtonTime >= MEDIUM)  //If Short Press Interval Passed
        ButtonState = Medium;                       //Button State Medium
    break;
// Detects Medium Button Hold
    case Medium: 
      if( input == HIGH ) //If Button Released
      {
        ButtonState = Idle; //Idle State
        return 2;           //Return 2
        }
      else if( millis() - ButtonTime >= LONG)     //If Medium Press Interval Passed
        ButtonState = Long;                         //Button State Long
    break;
// Detects Long Button Hold
    case Long: 
      if(input == HIGH)   //When Button is Released
      {
        ButtonState = Idle; //Idle State
        return 3;           //Return 3
      }
    break;
  } //End of Switch Statement
  return 0; //Returns 0 if button inactive
} // End of ButtonNextState Function

int Button()  // Easy to call/implement Button function
{
  return ButtonNextState( digitalRead( 4 ) );   //Returns ButtonNExtState with Button input
}//End of easy function



/////////////////////
//ENCODER FUNCTIONS//
void CWMonitor()    //Interupts program to detect Clock-Wise Encoder Movement
{
  if ( bitRead( PIND, 2 ) == bitRead( PIND, 3 ) ) //if input pins are equal,
    encoderValue++;                      //increment EncoderValue up
  else                                    //or else
    encoderValue--;                      //increment EncoderValue down
}

void CCWMonitor()   //Interupts program to detect Counter-Clock-Wise Encoder Movement
{
  if ( bitRead( PIND, 2 ) == bitRead( PIND, 3 ) ) //if input pins are equal,
    encoderValue--;                      //increment EncoderValue down
  else                                    //or else
    encoderValue++;                      //increment EncoderValue up
}

int EncoderDetent() //Detects full Encoder Detent
{
  // If full clockwise Detent
  if ( ( encoderValue - EncoderTracking ) >= DETENT )
  {
    EncoderTracking += DETENT;  //Reset Tracker
    return 1;                   //Return 1
  }
  // If full counterclockwise Detent
  else if ( encoderValue - EncoderTracking <= -DETENT )
  {
    EncoderTracking -= DETENT;  //Reset Tracker
    return -1;                  //Return -1
  }
  return 0; //Returns 0 for no action
}//End of Encoder Detent



/////////////////////
//CONTROL FUNCTIONS//
void _init_Controls()
{
  pinMode( 4, INPUT );  //Declares Button Pin
  
  attachInterrupt( digitalPinToInterrupt( 2 ), CWMonitor, CHANGE );  
  attachInterrupt( digitalPinToInterrupt( 3 ), CCWMonitor, CHANGE ); 
}

#endif
