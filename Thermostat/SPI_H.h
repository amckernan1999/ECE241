#ifndef SPI_H.h
#define SPI_H.h

// Software SPI code.
#define CS_Bit 2 /* A2 is bit 2 in PortC */
#define SClk_Bit 5 /* pin 13 is bit 5 in PortB */

#define MISO_Bit 4 /* pin 9 is bit 1 in PortB */
// Function that will set the defined pins as input and output
// in preparation for a software-based spi transfer.
void SW_SPI_Initialize()
{
  // Define Pins as input / output
  bitSet(DDRC, CS_Bit); // A2 is an output.
  bitClear(PORTC, CS_Bit); // and set it low DOUBLE CHECK THIS
  bitSet(DDRB, SClk_Bit); // pin 13 is an output.
  bitClear(PORTB, SClk_Bit); // Clock starts low.
 // bitSet(DDRB, MOSI_Bit); // pin 10 is an output.
  bitClear(DDRB, MISO_Bit); // MOSI is low
  // pinMode would be okay here,
  // but I used DDRX to show how they are used.
}// End of SW_SPI_Initialize
// This function will transfer the argument, Output, over the
// alternate SPI and returns the data sent back as its return value.
int SW_SPI()
{
  int Output;

  bitClear(PORTB, SClk_Bit); // Clock low.
  bitClear(PORTC, CS_Bit); // Chip Select low.
  
  for (int i = 15; i >= 0; i--)
  {
    // Set MOSI to value of bit i in Output.
    bitSet(PORTB, SClk_Bit); // clock high
    //bitWrite(PORTB, MOSI_Bit, bitRead(Output, i));
    
    // Set bit i in Output to MISO
    bitWrite(Output, i, bitRead(PINB, MISO_Bit));
   
    
    bitClear(PORTB, SClk_Bit); // Clock low.
  } // End of for loop.
  bitSet(PORTC, CS_Bit); // cs off
  
  return Output;
} // End of SW_SPI
#endif
