#pragma once
#include <Arduino.h>
#include <SPI.h>

void hardwareSetup(uint8_t ACK, uint8_t CHIPSELECT);

void startFrame();

void endFrame();

void setAckFlag();

void setIsr(uint8_t ACK);

void waitForAck();

uint8_t SpiTransfer(uint8_t dataSend);