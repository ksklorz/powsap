#include "serialESP.h"

void cSerialESP::serCRC(sPacket &packet)
{
    uint8_t crc = 0;
    uint8_t* packetData = reinterpret_cast<uint8_t*>(&packet);
    size_t packetSize = sizeof(packet) - sizeof(packet.crc);

    for (size_t i = 0; i < packetSize; i++)
        crc ^= packetData[i];

    // Set the CRC of the packet
    packet.crc = crc;
}

bool cSerialESP::checkCRC(sPacket &packet)
{
    // Calculate the CRC of the packet
    uint8_t crc = 0;
    uint8_t* packetData = reinterpret_cast<uint8_t*>(&packet);
    size_t packetSize = sizeof(packet) - sizeof(packet.crc);

    for (size_t i = 0; i < packetSize; i++)
        crc ^= packetData[i];

    // Check if the calculated CRC matches the packet CRC
    return crc == packet.crc;
}

uint8_t cSerialESP::sendPacket(sPacket packet)
{
    serCRC(packet);
    _serial.write((uint8_t *)&packet, sizeof(packet));
    return sizeof(packet);
}

bool cSerialESP::receivePacket(sPacket &packet)
{
    bool isOk = false;
    if (_serial.available() < sizeof(sPacket))
        return false;

    uint8_t startMarker;
    
    _serial.readBytes(&startMarker, 1);
    if (startMarker != 0xAA)
    {
        _serial.read();
        return false;
    }
    _serial.readBytes(&startMarker, 1);
    if (startMarker != 0x55)
    {
        return false;
    }

    packet.startMarker[0] = 0xAA;
    packet.startMarker[1] = 0x55;

    _serial.readBytes(((uint8_t*)&packet)+2, sizeof(packet)-2);

    return checkCRC(packet);

}

