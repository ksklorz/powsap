#pragma once
#include <Arduino.h>

namespace Tools
{
    void setCRC(uint8_t* data, size_t size);
    bool checkCRC(uint8_t* data, size_t size);
}