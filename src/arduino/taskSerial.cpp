#include "taskSerial.h"


#include "struct.h"

void cSerialThread::setup()
{
    _serial.begin();
}

void cSerialThread::mainLoop()
{
    // sPacket packet;
    // packet.device = eDeviceTemp;
    // packet.sensor = eSensorTemp;
    // packet.data = 2.1f;
    // packet.time = millis();
    // packet.cnt = 15;
    // packet.status = eStatusOK;

    // _serial.sendPacket((uint8_t*)&packet, sizeof(packet));
}

void cSerialThread::sendSerial(sPacket packet)
{
    _serial.sendPacket((uint8_t*)&packet, sizeof(packet));
}
