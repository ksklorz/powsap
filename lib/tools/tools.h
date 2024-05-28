#pragma once
#include <Arduino.h>

class cTools
{
public:
    static void setCRC(uint8_t* data, size_t size);
    static bool checkCRC(uint8_t* data, size_t size);
};