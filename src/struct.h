#pragma once

enum eDevice : uint8_t
{
    eDeviceTemp,
    eDeviceWindow,
    eDeviceLight
};

enum eDirection : uint8_t
{
    eDirCmd,
    eDirSensor
};

enum eDeviceStatus : uint8_t
{
    eStatusOK,
    eStatusError
};


struct sDataCmd
{
    float temp;
    float window;
    float light;
};

#pragma pack(1)
struct sPacket
{
    uint8_t startMarker[2];
    eDevice device;
    eDeviceStatus status;
    float data;
    uint32_t time;
    uint8_t cnt;
    uint8_t crc;
};