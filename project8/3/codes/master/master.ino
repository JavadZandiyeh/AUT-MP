#include <SPI.h>

#define LDR A0
#define LM35 A1

#define SS1 22
#define SS2 23

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

float fdata;

void loop(){

  int light_read = analogRead(LDR);
  float light_v = 5 * light_read / 1023.0;
  //float RLDR = (10000.0 * (5 - Vout))/Vout;
  //float lux = 500 / RLDR;
  Serial2.println(light_v);

  fdata = light_v;
  digitalWrite(SS1, LOW);
  
  for(int i=0;i<sizeof(float);i++) {
    data_send = *(((byte*)(&fdata))+i);
    data_get = SPI.transfer(data_send);
    delayMicroseconds(30);
  }
  
  digitalWrite(SS1, HIGH);
  delay(1000);



  int temp_read = analogRead(LM35);
  float temp_v = 5 * temp_read / 1023.0;
  float temp = 100 * temp_v;
  Serial2.println(temp);
  
  fdata = temp;
  digitalWrite(SS2, LOW);
  
  for(int i=0;i<sizeof(float);i++) {
    data_send = *(((byte*)(&fdata))+i);
    data_get = SPI.transfer(data_send);
    delayMicroseconds(30);
  }
  
  digitalWrite(SS2, HIGH);
  delay(1000);
}
