#pragma once
#include<arduino.h>

class cPotentiometer 
{
    uint8_t _pin; // pin
    static const uint16_t _minValue = 0;
    uint16_t _maxValue = 1023;

public:

    cPotentiometer() : _pin(0) {};
    cPotentiometer(uint8_t setPin) : _pin(setPin) 
        { pinMode(_pin, INPUT) ;};
    cPotentiometer(uint8_t setPin, uint16_t maxValue) : _pin(setPin), _maxValue(maxValue) 
        { pinMode(_pin, INPUT) ;};
    
    void setup(uint8_t setPin);


    //metoda odczytująca wartość zrzutowaną na 0-1
    float readNorm();
    float readScaled(float min, float max);
};