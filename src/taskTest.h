#pragma once
#include <Arduino.h>
#include "struct.h"

#ifdef ARDUINO_ARCH_ESP32

extern QueueHandle_t testQueue;

void testThread(void *pvParameters)
{
    float level = 1.0f;
    float step = 0.01f;
    int state = 0;
    while (true)
    {

        
        sPacket packet;
        packet.device = eDevice::eDeviceWindow;
        packet.sensor = eSensor::eSensorWindow;
        packet.data = level;
        xQueueSend(testQueue, &packet, portMAX_DELAY);

        switch (state)
        {
            case 0:
                level = 0;
                state = 1;
                break;
            case 1:
                level = .5f;
                state = 2;
                break;
            case 2:
                level = 1.0f;
                state = 3;
                break;
            case 3:
                level = .5f;
                state = 4;
                break;
            case 4:
                level = 0;
                state = 0;
                break;
        }
        
        vTaskDelay(3000 / portTICK_PERIOD_MS);

        // vTaskDelay(30 / portTICK_PERIOD_MS);
        // level += step;
        // 0.01f;
        // if (level <= -1.0f)
        // {
        //     step = 0.01f;
        // }
        // if (level >= 1.0f)
        // {
        //     step = -0.01f;
        // }
    }
}

#endif