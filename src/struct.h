#pragma once

enum eDevice : uint8_t
{
    eDeviceMaster = 0u,
    eDeviceLight = 1u,
    eDeviceWindow = 2u,
    eDeviceTemp = 3u
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
    eSensorLight = 0u,
    eSensorWindow = 1u,
    eSensorTemp = 2u
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