#include <SPI.h>

#define SS1 22

const String message = "Abolfazl 9831123\n";

volatile byte data_get, data_send;

void setup(){
  Serial2.begin(9600);
  pinMode(SS1, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  digitalWrite(SS1, HIGH);
}

void loop(){

  digitalWrite(SS1, LOW);
    
  for(int i=0;i<message.length();i++) {
    data_send = message.charAt(i);
    data_get = SPI.transfer(data_send);
    delayMicroseconds(20);
  }
  
  digitalWrite(SS1, HIGH);
  delay(1000);
}
