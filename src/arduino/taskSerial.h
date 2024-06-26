#pragma once
#include "taskThread.h"

#include <Arduino.h>

#include "struct.h"
#include "mySerial.h"
#include <SoftwareSerial.h>
class cSerialThread : public cThread 
{
    universalSerial<SoftwareSerial> _serial;

public: 
    void setup();
    void mainLoop();
        cSerialThread(uint32_t dT) : cThread(dT)
        ,_serial(2u, 3u) {};
    
    void sendSerial(sPacket packet); 

};

extern cSerialThread serial;


