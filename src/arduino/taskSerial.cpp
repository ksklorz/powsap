#include "taskSerial.h"


#include "struct.h"

void cSerialThread::setup()
{
    _serial.begin();
}

void cSerialThread::mainLoop()
{
    sPacket packet;
    packet.device = eDeviceTemp;
    packet.data = 2.1f;
    packet.time = millis();
    packet.cnt = 0;
    packet.status = eStatusOK;

    _serial.sendPacket(packet);
}
