#pragma once
#include<arduino.h>

class cPotentiometer 
{
    uint8_t _pin; // pin
    static const uint16_t _minValue = 0;
    static const uint16_t _maxValue = 1023;

public:
    cPotentiometer(uint8_t setPin) : _pin(setPin) 
        { pinMode(_pin, INPUT) ;};


    //metoda odczytująca wartość zrzutowaną na 0-1
    float readNorm();
};