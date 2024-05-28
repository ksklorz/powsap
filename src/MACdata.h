#pragma once

#include <map>
#include <array>
#include "struct.h"

#define MAC_ESP_1 {0x64, 0xE8, 0x33, 0x85, 0x3B, 0x40}

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

std::map<eDevice, sMACaddress> MACmap{
    {eDeviceWindow, MAC_ESP_1}

    // {2, NimBLEAddress("a4:c1:38:68:23:70")}
    // {3, NimBLEAddress("a4:c1:38:f2:af:2a")}  
};