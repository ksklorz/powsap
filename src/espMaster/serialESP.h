#pragma once
#include <Arduino.h>

#include <HardwareSerial.h>
#include "struct.h"

class cSerialESP
{
    HardwareSerial _serial;

    void serCRC(sPacket& packet);
    bool checkCRC(sPacket& packet);

    public:
    cSerialESP() : _serial(Serial0) {};
    void begin() {_serial.begin(115200);};
    uint8_t sendPacket(sPacket packet);
    bool receivePacket(sPacket& packet);
};