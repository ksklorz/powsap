#include "potentiometer.h"

float cPotentiometer::readNorm()
{
    uint16_t value =  analogRead(_pin); 
    float x = ((float)value - (float)_minValue)/(float)(_maxValue-_minValue);
    return x;
}