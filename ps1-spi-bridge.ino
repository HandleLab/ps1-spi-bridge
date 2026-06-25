#include <SPI.h>

#define ACK 2 
#define CHIPSELECT 10 

volatile bool ackFlag = false;

uint8_t IdRxPayload;

void setup() 
{
  pinMode(ACK, INPUT_PULLUP);
  
  pinMode(CHIPSELECT, OUTPUT);
  digitalWrite(CHIPSELECT, HIGH);

  SPI.begin();

  attachInterrupt(digitalPinToInterrupt(ACK), setAckFlag, FALLING);
}

void loop() {
  
  // setting up the spi protocole settings
  SPI.beginTransaction(SPISettings(250000, LSBFIRST, SPI_MODE3));
  
  // setting up the slave to receive data by is id
  digitalWrite(CHIPSELECT, LOW);
  SPI.transfer(0x01);
  while(!ackFlag);
  ackFlag = false;

  // sending the polling cmd to get buttons & joystick status and getting the id of the rx type 
  
  IdRxPayload = SPI.transfer(0x42);
  while(!ackFlag);
  ackFlag = false;
  
  switch(IdRxPayload)
  {
    case 0x41 :
    
      break;

    case 0x53 :
      
      break;
    
    case 0x73 :
        
      break;
    
    case 0x79 : 
      break;
    
    
  }

  digitalWrite(CHIPSELECT, HIGH);
}  

void setAckFlag()
{
  ackFlag = true;
}
