#include <SPI.h>
#include "PS1Controller.h"
#include "usbHidModule.h"

#define ACK 2 
#define CHIPSELECT 10 

void setup() 
{
  initModule(ACK, CHIPSELECT);
}

void loop() 
{
  
  uint8_t* ptrDataBuffer = pollController();
  formatInputReport(ptrDataBuffer);

}  


