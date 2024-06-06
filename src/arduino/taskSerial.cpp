#include "taskSerial.h"

#include "struct.h"
#include "global.h"

void cSerialThread::setup()
{
    _serial.begin();
    // Serial.println("SerialThread setup");
}

void cSerialThread::mainLoop()
{
    sPacket packet;
    // Serial.println("SerialThread");
    if(_serial.receivePacket((uint8_t*)&packet, sizeof(packet)))
    {
        panel.newSensorData(packet);
    }


}

void cSerialThread::sendSerial(sPacket packet)
{
    _serial.sendPacket((uint8_t*)&packet, sizeof(packet));
}
