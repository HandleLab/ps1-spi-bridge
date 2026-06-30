#pragma once
#include <stdint.h>
#include "SpiHardware.h"

void initModule(uint8_t ACK, uint8_t CHIPSELECT);

void readRxHeader();

void rxPayloadIdDispatcher();

void pollingData();

void defaultButtonsValue();