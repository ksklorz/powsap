#pragma once
#include "taskThread.h"
#include "config.h"

#include <Arduino.h>


// #include "config.h"
#include "display.h"
#include "potentiometer.h"

class cPanelThread : public cThread 
{
    cDisplay _display;
    cPotentiometer _potentiometer;
    
    void setup();
    void mainLoop();

    public:
        cPanelThread(uint32_t dT) : cThread(dT), _potentiometer(potPIN) {};

};