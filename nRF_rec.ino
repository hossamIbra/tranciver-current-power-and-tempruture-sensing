#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,9);
LiquidCrystal lcd2(22,23,24,25,26,27);
LiquidCrystal lcd3(34,35,36,37,38,39);



#include <SPI.h>

#include "RF24.h"


//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8

RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;

int msg[2];

void setup()

{
Serial.begin(9600);
lcd.begin(16,2);
lcd2.begin(16,2);
lcd3.begin(16,2);

radio.begin();

radio.openReadingPipe(1,pipe);

radio.startListening();

}

void loop()

{
    float current = 0;
  float maxCurrent = 0;
  float minCurrent = 1000;
 
   if (radio.available())

{ 
  for (int i=0 ; i<=200 ; i++)  //Monitors and logs the current input for 200 cycles to determine max and min current
  {
     radio.read(msg, sizeof(msg));
    current = msg[0];    //Reads current input and records maximum and minimum current
    if(current >= maxCurrent)
      maxCurrent = current;
    else if(current <= minCurrent)
      minCurrent = current;
      delay(1);
  }
  if (maxCurrent <= 517)
  {
    maxCurrent = 516;
  }
  double RMSCurrent = ((maxCurrent - 516)*0.707)/11.8337;    //Calculates RMS current based on maximum value
  

  float mv = ( msg[1]/1024.0)*5000; 
  float cel = mv/10;

 

  Serial.print(RMSCurrent);
  Serial.print("  ");
  Serial.print(cel);
  Serial.print("  ");
  Serial.println(RMSCurrent*110);

  lcd.clear();
  lcd2.clear();
  lcd3.clear();
  
  lcd.setCursor(4,0);
  lcd.print("current:");
  lcd.setCursor(5,1);
  lcd.print(RMSCurrent);
  lcd.print(" A");

  lcd2.setCursor(2,0);
  lcd2.print("tempreture:");
  lcd2.setCursor(5,1);
  lcd2.print(cel);
  lcd.print(" c");

  lcd3.setCursor(5,0);
  lcd3.print("power");
  lcd3.setCursor(5,1);
  lcd3.print(RMSCurrent*110);
  lcd.print(" W");
  
  //delay(300);
  

}
}
