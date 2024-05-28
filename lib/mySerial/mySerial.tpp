


template <class T>
inline uint8_t universalSerial<T>::sendPacket(uint8_t* packet, size_t size)
{
    cTools::setCRC(packet, size);

    _serial.write(0xAA);
    _serial.write(0x55);
    _serial.write((uint8_t *)packet, size);

    return size;
}

template <class T>
inline bool universalSerial<T>::receivePacket(uint8_t* packet, size_t size)
{
    
    bool isOk = false;
    if (_serial.available() < size+2)
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

    _serial.readBytes(((uint8_t*)packet), size);
    return cTools::checkCRC(packet, size);
}