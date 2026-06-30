#include "SpiHardware.h"

volatile bool ackFlag = false;

uint8_t InternalACK;
uint8_t InternalCHIPSELECT;

// SPI SETTINGS
const uint32_t CLKRate = 250000;
const uint8_t bitOrder = 0x0;
const uint8_t spiMode = 0x0C;

void hardwareSetup(uint8_t ACK, uint8_t CHIPSELECT)
{

  InternalACK = ACK;
  InternalCHIPSELECT = CHIPSELECT;

  pinMode(ACK, INPUT_PULLUP);
  
  pinMode(CHIPSELECT, OUTPUT);
  digitalWrite(CHIPSELECT, HIGH);

  SPI.begin();

  setIsr(ACK);
}


void setAckFlag()
{
  ackFlag = true;
}


void setIsr(uint8_t ACK)
{
  attachInterrupt(digitalPinToInterrupt(ACK), setAckFlag, FALLING);
}


void waitForAck()
{
  while(!ackFlag);
  ackFlag = false;
}


uint8_t SpiTransfer(uint8_t dataSend)
{
  uint8_t byteReceive = 0;

  byteReceive = SPI.transfer(dataSend);
  waitForAck();

  return byteReceive;
}

void startFrame()
{
  SPI.beginTransaction(SPISettings(CLKRate, bitOrder, spiMode));
  digitalWrite(InternalCHIPSELECT, LOW);
}

void endFrame()
{
  digitalWrite(InternalCHIPSELECT, HIGH);
  SPI.endTransaction(); 
}