#pragma once
#include <Arduino.h>

class cThread
{
    unsigned long _lastTime;
    uint32_t _deltaTime;

    virtual void mainLoop() = 0; //pure virtual
    virtual void setup() = 0; //pure virtual

    
public:
    cThread(uint32_t dT) : _lastTime(0u), _deltaTime(dT) {};

    void init();
    void update();

};