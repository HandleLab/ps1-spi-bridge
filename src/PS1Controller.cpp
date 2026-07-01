#include "PS1Controller.h"
#include "ProtocolConstants.h"



// buffer for header and payload
uint8_t rxHeader[3];
uint8_t rxDataBuffer[6];


void initModule(uint8_t ACK, uint8_t CHIPSELECT)
{
  hardwareSetup(ACK, CHIPSELECT);
}


void readRxHeader()
{
  startFrame();
  
  rxHeader[0] = SpiTransfer(PS1Protocol::slaveId);

  rxHeader[1] = SpiTransfer(PS1Protocol::pollinCmdId); 

  rxHeader[2] = SpiTransfer(PS1Protocol::dummyByte);

}


void pollingData(uint8_t forSize)
{
  for (size_t i = 0; i < forSize; i++)
  {
    rxDataBuffer[i] = SpiTransfer(PS1Protocol::dummyByte);
  }

  if (forSize == PS1Protocol::digitalControllerSize)
  {
    rxDataBuffer[2] = 0x80;
    rxDataBuffer[3] = 0x80;
    rxDataBuffer[4] = 0x80;
    rxDataBuffer[5] = 0x80;
  }
}


void defaultButtonsValue()
{
  rxDataBuffer[0] = 0xFF;
  rxDataBuffer[1] = 0xFF;
  rxDataBuffer[2] = 0x80;
  rxDataBuffer[3] = 0x80;
  rxDataBuffer[4] = 0x80;
  rxDataBuffer[5] = 0x80;
}


void rxPayloadIdDispatcher()
{

  memset(rxDataBuffer, 0, sizeof(rxDataBuffer));

  if(rxHeader[2] == PS1Protocol::sentinelHeader)
  { 
      switch(rxHeader[1])
    {
      case 0x41 :
        pollingData(PS1Protocol::digitalControllerSize);
        break;

      case 0x73 :
        pollingData(PS1Protocol::rumbleAnalogModeSize);
        break;
      
      default :
        defaultButtonsValue();
        break;

    }

    endFrame();
  }

  else
  {
    // putting default value in case of frame corruption
    defaultButtonsValue();
    endFrame();
  }
}


uint8_t* pollController()
{
  readRxHeader();
  rxPayloadIdDispatcher();

  return rxDataBuffer;
}