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

enum eSensor : uint8_t
{
    eSensorTemp,
    eSensorWindow,
    eSensorLight
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
    eDevice device;
    eDeviceStatus status;
    eSensor sensor;
    float data;
    uint32_t time;
    uint8_t cnt;
    uint8_t crc;
};