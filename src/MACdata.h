#pragma once

#include <map>
#include <array>
#include "struct.h"

#define MAC_ESP_1 {0x64, 0xE8, 0x33, 0x85, 0x3B, 0x40}
#define MAC_ESP_2 {0xDC ,0x54 ,0x75 ,0x61 ,0xCF ,0x88} //dfrobot
#define MAC_ESP_3 {0x64, 0xe8, 0x33, 0x86, 0x6a, 0x74}
#define MAC_ESP_4 {0x64 ,0xE8 ,0x33 ,0x11 ,0x75 ,0xAC}

// using MACAddress = std::array <uint8_t, 6>;

struct sMACaddress
{
    uint8_t mac[6];

    // operator sMACAddress() const {return mac; };
    bool operator== (const sMACaddress& other) const
    {
        for(int i = 0; i < 6; i++)
        {
            if(mac[i] != other.mac[i])
                return false;
        }
        return true;
    };

    sMACaddress& operator= (const sMACaddress& other)
    {
        for(int i = 0; i < 6; i++)
        {
            mac[i] = other.mac[i];
        }
        return *this;
    };

};

std::map<eDevice, sMACaddress> MACmap
{
    {eDeviceMaster, MAC_ESP_1},
    {eDeviceLight,  MAC_ESP_2},
    {eDeviceWindow, MAC_ESP_3},
    {eDeviceTemp,   MAC_ESP_4}
};