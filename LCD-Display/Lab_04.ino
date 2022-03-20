#include <LiquidCrystal.h>

LiquidCrystal Lcd(A5, A4, 5, 6, 7, 8 );
unsigned long timer;
unsigned long timer2;

int count;
int count2;

void setup() {
  Lcd.begin(2,16);
  timer = millis();
  timer2 = millis();
  count = 0;
 
 
}

void loop() {
  if(millis() - timer > 1000)
  {
  count++; 
  Lcd.clear();
  Lcd.print(count);
  Lcd.setCursor(0,1);
  Lcd.print(count2);
  timer +=1000;
  }
  
  if(millis() - timer2 > 100)
  { if(digitalRead(4) == LOW)
  {
    count2++;
    Lcd.clear();
    Lcd.print(count);
    Lcd.setCursor(0,1);
    Lcd.print(count2);
    timer2 +=100;
  }
  else{
     Lcd.clear();
     Lcd.print(count);
     count2 = 0;
    if(millis() - timer2 >500)
    {
      Lcd.setCursor(0,1);
      Lcd.print(count2);
    }
  }

}
}
