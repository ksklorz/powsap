#pragma once
#include <Arduino.h>
#include "struct.h"

#ifdef ARDUINO_ARCH_ESP32

extern QueueHandle_t testQueue;

void testThread(void *pvParameters)
{
    float level = 1.0f;
    float step = -0.01f;
    while (true)
    {
        sPacket packet;
        packet.device = eDevice::eDeviceLight;
        packet.sensor = eSensor::eSensorLight;
        packet.data = level;
        xQueueSend(testQueue, &packet, portMAX_DELAY);

        vTaskDelay(100 / portTICK_PERIOD_MS);
        level += step;
        0.01f;
        if (level <= 0.0f)
        {
            step = 0.01f;
        }
        if (level >= 1.0f)
        {
            step = -0.01f;
        }
    }
}

#endif