#ifndef Game_2_H
#define Game_2_H

int RANDOMSEED = 9;
char NEW = (char)0xDB;
char BOMB = '*';
int _g2_Win_Flag = 0;
unsigned long _g2_Timer;

char _g2_Bomb_Key[4][21];   //Master list of all bomb locations

int _g2_cursor_row = 0;     //row value for cursor
int _g2_cursor_column = 0;  //column value for coaster


void internal_Hi_Score();
////////////////////////////
//randomly places 10 bombs//
void _g2_Key_Construct() 
{ 
  for ( int bomb_total = 0; bomb_total < 10; bomb_total++ )
    {
    int bomb_column = random( 20 );   //Chooses column randomly
    int bomb_row = random( 4 );       //Chooses row randomly
    if( _g2_Bomb_Key[bomb_row][bomb_column] == BOMB)  //If the spot is a bomb add a another iteration
    {bomb_total--;}
    _g2_Bomb_Key[bomb_row][bomb_column] = BOMB;   
    int _g2_Bomb_Total = bomb_total;
    }

  
  for ( row = 0; row < 4; row++ )
  { 
    
    
    for ( col = 0; col < 20; col++ )
    {
      if( _g2_Bomb_Key[row][col] != BOMB)
      {_g2_Bomb_Key[row][col] = BLANK;}        // Make every non bomb Position in key blank
      _g2_Bomb_Key[row][20] = 0;          // Final Row Position is Terminator
    } 
         
   } 

   for ( row = 0; row < 4; row++ )
   {
    for ( col = 0; col < 20; col++ )
    {
      int _g2_Bomb_Near = 0; //Var used to keep track of bombs in adjacent spaces
      
      if( _g2_Bomb_Key[row][col] != BOMB)
      {
        if( row == 0)
        {
          if(col == 0)                                                    //Each row has special cases on edge
          {                                                               // col =0 and col 19 need to be special
            if(_g2_Bomb_Key[row][col + 1] == BOMB){_g2_Bomb_Near++;}      //cases in each row
            if(_g2_Bomb_Key[row + 1][col] == BOMB){_g2_Bomb_Near++;}      // row 2 and 3 can be itereated the same
            if(_g2_Bomb_Key[row + 1][col + 1] == BOMB){_g2_Bomb_Near++;}  //but row 1 and 4 are unique and need to be 
          }                                                               // iterated seperatly

          if(col == 19)
          {
            if(_g2_Bomb_Key[row][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col] == BOMB) {_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col - 1] == BOMB) {_g2_Bomb_Near++;}            
          }

          if(col > 0 and col < 19)
          {
            if(_g2_Bomb_Key[row][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col + 1] == BOMB){_g2_Bomb_Near++;}
          }
        }
        

        if( row == 1 or row == 2)
        {
          if(col == 0)
          {
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col] == BOMB){_g2_Bomb_Near++;}
          }

          if(col == 19)
          {
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col - 1] ==BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            
          }

          if(col > 0 and col < 19)
          {
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col - 1] == BOMB) {_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col] == BOMB) {_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col + 1] == BOMB) {_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col + 1] == BOMB) {_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row + 1][col + 1] == BOMB) {_g2_Bomb_Near++;}    
          }  
        }
    
        if( row == 3)
         {
          
          if(col == 0)
          {
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col + 1] == BOMB){_g2_Bomb_Near++;}
          }

          if(col ==19)
          {
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col - 1] == BOMB){_g2_Bomb_Near++;}
          }

          if(col > 0 and col < 19)
          {
            if(_g2_Bomb_Key[row][col + 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col - 1] == BOMB){_g2_Bomb_Near++;}
            if(_g2_Bomb_Key[row - 1][col] == BOMB){_g2_Bomb_Near++;} 
            if(_g2_Bomb_Key[row - 1][col + 1] == BOMB){_g2_Bomb_Near++;}
         }
              
      } 
      if(_g2_Bomb_Near != 0){_g2_Bomb_Key[row][col] = _g2_Bomb_Near + '0';}    
     }
   
   }
 
 }
}

///////////////////////////////
//Initiates Screen for Game 1//
void _g2_Init_Screen()  // sets  Screen
{
  // For every Row
  for ( row = 0; row < 4; row++ )
  {
    // For every Column
    for ( col = 0; col < 20; col++ )
    {
      Screen[row][col] = NEW; // Make Position starter
    } // End of column loop
    Screen[row][20] = 0;      // Final Row Position is Terminator
  } 
} 

void _g2_Clear_Bomb_Key()  // Clears Data in Screen
{
  // For every Row
  for ( row = 0; row < 4; row++ )
  {
    // For every Column
    for ( col = 0; col < 20; col++ )
    {
      _g2_Bomb_Key[row][col] = BLANK; // Make Position Blank
    } // End of column loop
    _g2_Bomb_Key[row][20] = 0;      // Final Row Position is Terminator
  } // End of row loop
} // End of ClearScreen


void _g2_Init()
  { 
    time_modifier = 400;
    _g2_Clear_Bomb_Key();
    ClearScreen();
    randomSeed(analogRead(RANDOMSEED));  //random in arduino will start the same every time without a pin set to seed
    _g2_Key_Construct();
    _g2_Init_Screen();
    _g2_Timer = millis();
    LCD.blink();    //blink cursor to keep track of it
    
    
  }

void _g2_Cursor_Tracking(int upDown)
  {
   if(upDown== 1) //encoder returns 1 for clockwise movement
   {
    
    if( _g2_cursor_column != 19)  //checks for wrapping
      {_g2_cursor_column++;}
  
    
    else 
      {
        if( _g2_cursor_row != 3) //checks for wrapping
        {
          _g2_cursor_row++;
          _g2_cursor_column = 0;
        }

        else
        {
          _g2_cursor_column = 0;  //special case 19x3 must wrap to 0x0
          _g2_cursor_row = 0;
        }
       }
   }
   

   if(upDown== -1) //Returns -1 for counter clockwise rotation
   {
    
    if( _g2_cursor_column != 0) //checks for wrapping
      {_g2_cursor_column--;}
  
    
    else
      {
        if( _g2_cursor_row != 0) //checks for special case 0x0
        {
          _g2_cursor_row--;
          _g2_cursor_column = 19;
        }

        else
        {
          _g2_cursor_row = 3;
          _g2_cursor_column = 19; //sets to 3x19 for going left at 0x0
        }
  }
   }
    LCD.setCursor(_g2_cursor_column ,_g2_cursor_row );  //sets cursor to encoder value for row and column
    
   }

void _g2_GameOver() //This is mainly an animation to show the user that they lost
{
  delay(500); //used to show user lost
  ClearScreen(); 
  LCD.noBlink();
  Screen[_g2_cursor_row][_g2_cursor_column] = BOMB;
  SendScreen();
  delay(1500); //used to show user lost
  ClearScreen();
 
  Screen[1][5] = 'G'; // Sets screen to print GAME OVER
  Screen[1][6] = 'A';
  Screen[1][7] = 'M';
  Screen[1][8] = 'E';
  Screen[1][9] = ' ';
  Screen[1][10] = 'O';
  Screen[1][11] = 'V';
  Screen[1][12] = 'E';
  Screen[1][13] = 'R';
}

// Variable used as clock settings.
int Hours, Minutes, Seconds;

void UpdateClock()  //Used for user score
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
      Minutes = 0;
     
    } // End of Minutes test
  } // End of Seconds test
} // end of UpdateClock()

void _g2_Game_Win() //Just prints victory and clear screen, no animation or time spent
{
  LCD.noBlink();
  ClearScreen();
  Screen[0][6] = 'V'; //Prints VICTORY on screen
  Screen[0][7] = 'I';
  Screen[0][8] = 'C';
  Screen[0][9] = 'T';
  Screen[0][10] = 'O';
  Screen[0][11] = 'R';
  Screen[0][12] = 'Y';

  int _g2_Score = _g2_Timer - millis(); //used to increase Second after 1000ms
  _g2_Score /= 1000;
  LCD.setCursor(0,2);   //ALL formating for printing highscore and current score
  LCD.print("Best Time: "); 
  LCD.print('0'); //ORIGINALLY I had 2 seperate vars stored for _g2_Hi_Score but i replaced it with 1 since i had a highscore of less than a minute
  LCD.print(':');   //since its stored in the eeprom i no longer need to write and read twice as much since it will always be 0
  LCD.print(_g2_Hi_Score);
  LCD.setCursor(0,3);
  LCD.print("Your Time: ");
   LCD.print(Minutes);
  LCD.print(':');
  if( Seconds < 10)LCD.print('0');
  LCD.print(Seconds);
  
  
}

void _g2_Win_Check()
{
  int _g2_Bombs_Left = 0;

  for ( row = 0; row < 4; row++ )
  {
    for ( col = 0; col < 20; col++ )
    {
      if(Screen[row][col] == NEW){_g2_Bombs_Left++;} //# of unclicked tiles
    }
  }

  if(_g2_Bombs_Left == 10)
  { if(Minutes == 0)
  {if(Seconds < _g2_Hi_Score) //check for highscore
    {
      new_Hi_Score(Seconds, 2); // use this to write to eeprom
    }
  }
    _g2_Win_Flag = 1; // this flag signals the timer to stop seconds later
    _g2_Game_Win();
   } //10 is the number of bombs in bomb key
}

void _g2_Button_Tracking(int button)
{
  if(button == 1)
    {
      Screen[_g2_cursor_row][_g2_cursor_column] = _g2_Bomb_Key[_g2_cursor_row][_g2_cursor_column];
      if(Screen[_g2_cursor_row][_g2_cursor_column] == BOMB) //if bomb tile clicked you lose
      {
        _g2_GameOver();
      }
    }

}



void _g2_Frame(int button, int upDown)
{
  _g2_Cursor_Tracking(upDown);  //tracks cursor
  _g2_Button_Tracking(button);  // tracks button
  _g2_Win_Check();  //checks if user won and will set flag if they did
  SendScreen(); //sends screen to lcd
  LCD.setCursor(_g2_cursor_column, _g2_cursor_row );  //adjusts where the cursor is every frame
  if(millis() - _g2_Timer >= 1000 and _g2_Win_Flag == 0)  // used to keep track of time for end score
  {UpdateClock();
  _g2_Timer += 1000;}
  if (_g2_Win_Flag == 1){_g2_Game_Win();} //checks if user one
}
  

#endif 
