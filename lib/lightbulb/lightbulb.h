#pragma once
#include <Arduino.h>

class cLightBulb
{
    uint8_t _pin;
    uint8_t _pwmCanal;

    static const uint8_t _resolution = 10;
public:
    cLightBulb(uint8_t pin, uint8_t canal);
    void setBrightness(float brightness);
};