#ifndef Screen_H
#define Screen_H

// Imports and declares LCD Driver
#include <LiquidCrystal.h>
LiquidCrystal LCD( A5, A4, 5, 6, 7, 8 ); 

// Defines character Constants
char STAR = '*';
char BLANK = ' ';

char Screen[4][21]; // Declares Screen Data
int row, col;       // Declares for loop variables

void row_line( int r, int col1, int col2, char input )
{
  for ( col = col1; col <= col2; col++)
  {
    Screen[r][col] = input;
  }
}

void col_line( int c, int row1, int row2, char input )
{
  for ( row = row1; row <= row2; row++)
  {
    Screen[row][c] = input;
  }
}

void ClearScreen()  // Clears Data in Screen
{
  // For every Row
  for ( row = 0; row < 4; row++ )
  {
    // For every Column
    for ( col = 0; col < 20; col++ )
    {
      Screen[row][col] = BLANK; // Make Position Blank
    } // End of column loop
    Screen[row][20] = 0;      // Final Row Position is Terminator
  } // End of row loop
} // End of ClearScreen


void SendScreen() // Prints out Screen Data to LCD
{
  // For every Row
  for ( row = 0; row < 4; row++ )
  {
    LCD.setCursor( 0, row );  //  Set Cursor equal to row
    LCD.print( Screen[row] ); // Print Row
  } // End of row loop
} // End of SendScreen


void shiftRight(int start, int finish) // Shifts all data on screen right
{
  // For every row
  for ( row = 0; row < 4; row++ )
  {
    // For every column
    for ( col = finish; col > start; col-- )
    {
      int left = col - 1; // Set left to column selected minus one
      Screen[row][col] = Screen[row][left];   // set column selected to column to left
    } // End of column loop
    Screen[row][0] = BLANK; // Sets first column blank
    Screen[row][20] = 0;    // Terminates final column
  } // End of row loop
} // End of shiftRight


void randomStarLeft(int chance) // Sets star to first column with percentage chance
{
  // For every row
  for( row = 0; row < 4; row++ )
  {
    if ( random( 0, 100 ) <= chance ) //given percentage chance
    {
      Screen[row][0] = STAR;            // Star will appear
    } // End of chance
  } // End of Row loop
} // End of randomStarLeft


void _init_Screen() // Initializes screen
{
  LCD.begin( 20, 4 ); // Initializes screen
  ClearScreen();      // Clears screen data
  SendScreen();       //Sends cleared screen
}

#endif
