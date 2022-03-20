#include <SPI.h>

unsigned long timer;

float tempC;
float tempF;


float ReadTemperature() {
  digitalWrite(10, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  int TempBits = ( SPI.transfer16(0) >> 3 ) & 0x0fff;
  digitalWrite(10, HIGH);
  tempC = 0.25 * (float) TempBits;
  tempF = 1.8 * tempC + 32.0;
 
}

void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  timer = millis();
}

void loop() {
  if (millis() - timer >= 1000) {
    ReadTemperature();
    
    Serial.print("Temperature in Celsius = ");
    Serial.print(tempC);
    Serial.print("\n");
    Serial.print("Temperature in Farenheit = ");
    Serial.print(tempF);
    Serial.print("\n");
    
    timer = millis();
  }
}
