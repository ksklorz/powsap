#include "serialArduino.h"

void cSerialArd::setCRC(sPacket &packet)
{
    // Calculate the CRC of the packet
    uint8_t crc = 0;
    uint8_t* packetData = reinterpret_cast<uint8_t*>(&packet);
    size_t packetSize = sizeof(packet) - sizeof(packet.crc);

    for (size_t i = 0; i < packetSize; i++)
        crc ^= packetData[i];

    // Set the CRC of the packet
    packet.crc = crc;
}

bool cSerialArd::checkCRC(sPacket &packet)
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

uint8_t cSerialArd::sendPacket(sPacket packet)
{
    // Convert the packet structure to a byte array
    setCRC(packet);
    uint8_t* packetData = reinterpret_cast<uint8_t*>(&packet);
    size_t packetSize = sizeof(packet);

    // Send the packet byte by byte
    for (size_t i = 0; i < packetSize; i++) {
        Serial.write(packetData[i]);
    }

    // Return the number of bytes sent
    return packetSize;
}

bool cSerialArd::receivePacket(sPacket &packet)
{
    // Check if there is data available to read from the serial port
    if (Serial.available() >= sizeof(sPacket))
    {
        Serial.readBytes((uint8_t*)&packet, sizeof(packet));
        if(checkCRC(packet))
            return true;
    }

    return false; // No valid packet received
}
