#pragma once


#include <Arduino.h>
#include <struct.h>
#include <SoftwareSerial.h>

class cSerialArd
{
    SoftwareSerial _serial;

private:
        void setCRC(sPacket& packet);
        bool checkCRC(sPacket& packet);

public:
    cSerialArd(uint8_t rx, uint8_t tx) : _serial(rx, tx) {};
    void begin() {_serial.begin(115200);};
    uint8_t sendPacket(sPacket packet);
    bool receivePacket(sPacket& packet);
    
};