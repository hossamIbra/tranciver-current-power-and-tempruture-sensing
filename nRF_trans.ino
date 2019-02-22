#include <SPI.h>

#include "RF24.h"

int msg[2]; //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8

RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;

float val;

void setup(void)

{
Serial.begin(9600);
radio.begin();

radio.openWritingPipe(pipe);
//radio.setRetries(15, 15);

}

void loop(void)

{
msg[0]=analogRead(A0);
msg[1]=analogRead(A1);

Serial.print(msg[0]);
Serial.print("  ");
Serial.println(msg[1]);
radio.write(msg,sizeof(msg));


}
