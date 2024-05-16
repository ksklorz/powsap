#pragma once
#include<arduino.h>

#include<OneWire.h>
#include<DallasTemperature.h>


//klasa obsługująca czujnike temperatury dallas DS18B20 po protokole one-wire
class cTermometer
{
    // uint8_t _pin; //pin do podpiety do 

    OneWire _ow;
    DallasTemperature _sensor;

    public:
    cTermometer(uint8_t pin) : _ow(pin), _sensor(&_ow) {};
    void init();

    float readTemperature();

};