#pragma once


#include <Arduino.h>
#include <struct.h>

class cSerialArd
{
private:
        void setCRC(sPacket& packet);
        bool checkCRC(sPacket& packet);

public:

    uint8_t sendPacket(sPacket packet);
    bool receivePacket(sPacket& packet);
    
};