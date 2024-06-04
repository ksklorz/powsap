#pragma once
#include <Arduino.h>
#include "tools.h"
// #include <HardwareSerial.h>
// #include <SoftwareSerial.h>

template <class T>
class universalSerial
{
private:
    T _serial;
public:
    universalSerial(T& _serial) : _serial(_serial) {};
    universalSerial(uint8_t rx, uint8_t tx) : _serial(rx,tx) {};
    universalSerial(uint8_t rx, uint8_t tx, bool inverse) : _serial(rx,tx, inverse) {};
    void begin() {_serial.begin(9600);};
    uint8_t sendPacket(uint8_t* packet, size_t size);
    bool receivePacket(uint8_t* packet, size_t size);
    size_t available() {return _serial.available();};
    void readBytes(uint8_t* buffer, size_t size) {_serial.readBytes(buffer, size);};
};


#include "mySerial.tpp"
