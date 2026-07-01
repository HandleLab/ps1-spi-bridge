#include "usbHidModule.h"
#include "ProtocolConstants.h"

// record data struct
struct gamePad
{
    uint16_t allButtons;
    uint8_t LX;
    uint8_t LY;
    uint8_t RX;
    uint8_t RY;
}recordData;


void formatInputReport(uint8_t* dataBuffer)
{

    recordData.allButtons = (dataBuffer[PS1Protocol::offsetButtonHigh] << 8) | dataBuffer[PS1Protocol::offsetButtonLow];
    recordData.allButtons = ~recordData.allButtons;

    recordData.RX = dataBuffer[PS1Protocol::offsetRX];
    recordData.RY = dataBuffer[PS1Protocol::offsetRY];
    recordData.LX = dataBuffer[PS1Protocol::offsetLX];
    recordData.LY = dataBuffer[PS1Protocol::offsetLY];
}