#pragma once
#include "taskThread.h"

#include <Arduino.h>

#include "struct.h"
#include "serialArduino.h"

class cSerialThread : public cThread 
{


    cSerialArd _serial;

public: 
    void setup();
    void mainLoop();
        cSerialThread(uint32_t dT) : cThread(dT)
        ,_serial(5u,6u) {};

};


