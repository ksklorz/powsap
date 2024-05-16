#pragma once
#include <Arduino.h>


class cRelay
{
    uint8_t _pin;
    uint32_t _ticksInterval;
    uint32_t _ticksHigh;
    uint32_t _counter;

    bool _ONstate; //stan dla wlaczonego 

    public:
        cRelay(uint8_t pin);
        void setWidth(float width); //ustawienie wypelnienia 0-1
        void update();
        void setOnstate(bool newON) {_ONstate = newON;};
};