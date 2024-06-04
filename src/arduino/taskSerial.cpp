#include "taskSerial.h"


#include "struct.h"

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
        Serial.println(packet.data);

    // size_t x = _serial.available();

    // uint8_t buffer[200];
    // if(x)
    // {
    //     _serial.readBytes(buffer, x);
    //     for(size_t i = 0; i < x; i++)
    //     {
    //         Serial.print(buffer[i], HEX);
    //         Serial.print(" ");
    //     }
    //     Serial.println();
    // }
}

void cSerialThread::sendSerial(sPacket packet)
{
    _serial.sendPacket((uint8_t*)&packet, sizeof(packet));
}
