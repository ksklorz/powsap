#pragma once

enum eDevice
{
    eDeviceTemp,
    eDeviceWindow,
    eDeviceLight
};

enum eDirection
{
    eDirCmd,
    eDirSensor
};

enum eDeviceStatus
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

struct sPacket
{
    eDevice device;
    eDeviceStatus status;
    float data;
    uint32_t time;
    uint8_t cnt;
    uint8_t crc;
};