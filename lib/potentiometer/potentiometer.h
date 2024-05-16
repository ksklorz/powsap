#pragma once
#include<arduino.h>

class cPotentiometer 
{
    uint8_t _pin; // pin
    static const uint16_t _minValue = 0;
    static const uint16_t _maxValue = 1023;

public:

    cPotentiometer() : _pin(0) {};
    cPotentiometer(uint8_t setPin) : _pin(setPin) 
        { pinMode(_pin, INPUT) ;};
    
    void setup(uint8_t setPin);


    //metoda odczytująca wartość zrzutowaną na 0-1
    float readNorm();
};