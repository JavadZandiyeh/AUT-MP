#include <SPI.h>

#define SS1 22
#define SS2 23

const String message1 = "Abolfazl\n";
const String message2 = "Hello Abolfazl\n";


volatile byte data_get, data_send;

void setup(){
  Serial2.begin(9600);
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
}

void loop(){

  digitalWrite(SS1, LOW);
  
  for(int i=0;i<message1.length();i++) {
    data_send = message1.charAt(i);
    data_get = SPI.transfer(data_send);
    delayMicroseconds(30);
  }
  
  digitalWrite(SS1, HIGH);
  delay(1000);

  
  digitalWrite(SS2, LOW);
  
  for(int i=0;i<message2.length();i++) {
    data_send = message2.charAt(i);
    data_get = SPI.transfer(data_send);
    delayMicroseconds(30);
  }
  
  digitalWrite(SS2, HIGH);
  delay(1000);
}
