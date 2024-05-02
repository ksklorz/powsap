#pragma once
#include "taskThread.h"
#include <Arduino.h>

#include "config.h"
#include "termometer.h"
#include "PID.h"
#include "relay.h"

class cHeaterThread : public cThread 
{
    cTermometer _termometer;
    cPID _pid; 
    cRelay _heater;
    
    void setup();
    void mainLoop();

    public:
        cHeaterThread(uint32_t dT) : cThread(dT), _pid((float)HEATER_DELAY/1000.0f, 0.0f, 1.0f),_termometer(tempPIN), _heater(relayPIN) {};

};