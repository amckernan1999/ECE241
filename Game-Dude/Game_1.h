#ifndef Game_1_H
#define Game_1_H

unsigned long gameTimer = 0;
int player = 0;
int lives = 3;
int score;

int attackFlag = 0;
int previous_player = 0;

int time_modifier = 0;
int asteroid_modifier = 0;

char BLASTER = '<';


/////////////////
// GAME STATES //
// Initializes new game variables
void _g1_Init()
{
  LCD.noBlink();
  ClearScreen();
  SendScreen();
  lives = 3;
  row_line(3, 17, 19, BLASTER);
  col_line(16, 0, 3, '|');
  time_modifier = 0;
  asteroid_modifier = 0;
  attackFlag = 0;
  previous_player = player;
  score= 0;
  gameTimer = millis();
}

// Displays GameOver Screen then reinitializes game.
void _g1_GameOver()
{
  if( lives < 0 or score >= 1000 or (( millis() - gameTimer ) / 1000 ) >= 1000)
  {
    ClearScreen();
    SendScreen();
  
    LCD.setCursor(8, 0);
    LCD.print( "GAME" );
    LCD.setCursor(8, 1);
    LCD.print( "OVER" );

    int final_score = score * (( millis() - gameTimer ) / 1000 );
    if( final_score >= _g1_Hi_Score )
    {
      new_Hi_Score(final_score, 1);
      LCD.setCursor(0, 2);
      LCD.print( "NEW ");
    }
    else
    {
      LCD.setCursor(0, 2);
      LCD.print( "   SCORE:");
      LCD.print( final_score );
    }
    LCD.setCursor(0, 3);
    LCD.print( "HI-SCORE:" );
    LCD.print( _g1_Hi_Score );
    
    delay(5000);
    
    _g1_Init();
  }
}



//////////////////
// GAME OBJECTS //
// Prints Time, Score, and remaining lives to right of screen
void _g1_Interface()
{
  int current_time = (( millis() - gameTimer ) / 1000 );
  
  Screen[0][17] = 48 + current_time / 100;
  Screen[0][18] = 48 + ( current_time % 100 ) / 10;
  Screen[0][19] = 48 + (( current_time % 100) % 10 );
  
  Screen[1][17] = 48 + score / 100;
  Screen[1][18] = 48 + ( score % 100 ) / 10;
  Screen[1][19] = 48 + (( score % 100) % 10 );

  if( lives == 0)
    Screen[3][19] = BLANK;
  else if( lives == 1)
    Screen[3][18] = BLANK;
  else if( lives == 2)
    Screen[3][17] = BLANK;
}


// Handles short Button Press, acts as laser destroying asteroids
void _g1_Shoot( int button )
{
  if( attackFlag <= 0 )
    previous_player = player;
    
  if( attackFlag < 0 )
    attackFlag += 1;
  else if( attackFlag >= 5 or previous_player != player)
  {
    row_line(previous_player, 11, 15, BLANK);
    attackFlag = -5;
  }
  else if( button == 1 or attackFlag > 0)
  {
    if( attackFlag == 0 )
    {
      time_modifier += 10;
      asteroid_modifier += 1;
    }
    
    for( col = 10; col <= 14; col++ )
    {
      if( Screen[player][col] == STAR )
        score += 5;
    }
    
    row_line(player, 10, 13, '-');
    Screen[player][14] = '~';

    previous_player = player;
    attackFlag += 1;
  }
}

void _g1_Player( int up_down )
{
  if( Screen[player][15] == BLANK or
  Screen[player][15] == '~' or Screen[player][15] == '-' )
  {
    player -= up_down;
    if( player <= -1 )
      player = 0;
    else if( player >= 4)
      player = 3;
    Screen[player][15] = BLASTER;
  }
  else
  {
    Screen[player][15] = 'X';
    lives -= 1;
    SendScreen();
    delay(1000);
    
    player -= up_down;
    if( player <= -1 )
      player = 0;
    else if( player >= 4 )
      player = 3;
    Screen[player][15] = BLASTER;
  }
}

////////////////////
// GAME FUNCTIONS //
void _g1_Frame( int button, int upDown )
{
  if((( millis() - gameTimer ) / 1000 ) % 10 == 0 )
    time_modifier += 5;
  _g1_GameOver();
  _g1_Interface();
  
  randomStarLeft( 10 + asteroid_modifier );
  shiftRight( 0, 15 );
  
  _g1_Player( upDown );
  _g1_Shoot( button );
  
  SendScreen();
}

#endif
