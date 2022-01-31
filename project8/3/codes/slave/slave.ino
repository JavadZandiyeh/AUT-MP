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

int pos = 0;
float fdata = 0;

void loop()
{
  if(received)
  {
    *(((byte*)(&fdata))+pos) = data_get;
    pos = (pos + 1) % sizeof(float);
    received = false;
    if(pos == 0)
      Serial2.println(fdata);
  }
}
