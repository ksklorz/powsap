#include "tools.h"

void cTools::setCRC(uint8_t *data, size_t size)
{
    uint8_t crc = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        crc ^= data[i];
    }
    data[size - 1] = crc;
}

bool cTools::checkCRC(uint8_t *data, size_t size)
{
    uint8_t crc = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        crc ^= data[i];
    }
    return crc == data[size - 1];
}