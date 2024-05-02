#include "potentiometer.h"

void cPotentiometer::setup(uint8_t setPin)
{
    _pin = setPin; 
    pinMode(_pin, INPUT) ;
}

float cPotentiometer::readNorm()
{
    uint16_t value =  analogRead(_pin); 
    float x = ((float)value - (float)_minValue)/(float)(_maxValue-_minValue);
    return x;
}