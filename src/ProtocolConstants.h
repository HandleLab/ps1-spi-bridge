#pragma once
#include <Arduino.h>

namespace PS1Protocol
{
    constexpr uint8_t slaveId = 0x01;
    constexpr uint8_t pollinCmdId = 0x42;
    constexpr uint8_t dummyByte = 0x0;

    constexpr uint8_t sentinelHeader = 0x5A;

    // payload size
    constexpr uint8_t digitalControllerSize = 2;
    constexpr uint8_t rumbleAnalogModeSize = 6;

    // data payload offset
    constexpr uint8_t offsetButtonHigh = 0;
    constexpr uint8_t offsetButtonLow = 1;
    constexpr uint8_t offsetRX = 2;
    constexpr uint8_t offsetRY = 3;
    constexpr uint8_t offsetLX = 4;
    constexpr uint8_t offsetLY = 5;
}