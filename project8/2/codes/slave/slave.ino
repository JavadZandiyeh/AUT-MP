#include<SPI.h>

volatile boolean received;
volatile byte data_get, data_send;

void setup()
{
  Serial2.begin(9600);
  pinMode(MISO,OUTPUT);
  pinMode(SS,INPUT);
  
  SPCR |= _BV(SPE); // Setting the control register Slave bit (SPE is the bit that specifies being Slave)    Same as (1 << SPE)
  received = false;
  
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect)
{
  data_get = SPDR;  //  Saving Data Register into variable
  received = true;
}

char last = '\n', c;
String tmp = "";

void loop()
{
  if(received)
  {
    c = data_get;
    if(c!='\n')
      tmp += c;
      
    //SPDR = data_send; // Setting Data Register for sending data
    received = false;

    if(c == '\n') {
      Serial2.println(tmp);
      tmp = "";
    }
  }
}
