#include "PS1Controller.h"

constexpr uint8_t slaveId = 0x01;
constexpr uint8_t pollinCmdId = 0x42;
constexpr uint8_t dummyByte = 0x0;

constexpr uint8_t sentinelHeader = 0x5A;

uint8_t rxHeader[3];
uint8_t rxDataBuffer[6];

void initModule(uint8_t ACK, uint8_t CHIPSELECT)
{
  hardwareSetup(ACK, CHIPSELECT);
}

void readRxHeader()
{
  startFrame();
  
  rxHeader[0] = SpiTransfer(slaveId);

  rxHeader[1] = SpiTransfer(pollinCmdId); 

  rxHeader[2] = SpiTransfer(dummyByte);

}

void rxPayloadIdDispatcher()
{
    if(rxHeader[2] == sentinelHeader)
  { 
      switch(rxHeader[1])
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
  }

  else
  {
    // putting default value in case of frame corruption
    rxDataBuffer[0] = 0xFF;
    rxDataBuffer[1] = 0xFF;
    rxDataBuffer[2] = 0x80;
    rxDataBuffer[3] = 0x80;
    rxDataBuffer[4] = 0x80;
    rxDataBuffer[5] = 0x80;

    endFrame();
  }
}