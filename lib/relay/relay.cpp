#include "relay.h"

cRelay::cRelay(uint8_t pin) : _pin(pin), _ticksInterval(1000u), _ticksHigh(0u), _counter(0u), _ONstate(HIGH)
{
    pinMode(_pin, OUTPUT);
}

void cRelay::setWidth(float width)
{
    _ticksHigh = width * _ticksInterval;
}

void cRelay::update()
{
    bool on = (_counter < _ticksHigh);
    on = (on == _ONstate);

    if(++_counter >= _ticksInterval)
        _counter = 0; 

    digitalWrite(_pin, on);
}
