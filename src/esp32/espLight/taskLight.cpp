#include "taskLight.h"
#include "lightbulb.h"
#include "config.h"
#include "struct.h"

void lightBulbThread(void *pvParameters)
{
    cLightBulb lightbulb(PIN_LIGHT, 0);
    while (1)
    {   
        sPacket packet;
        if(xQueueReceive(setLightQueue, &packet, portMAX_DELAY))
        {
            if(eSensor::eSensorLight == packet.sensor)
            {
                lightbulb.setBrightness(packet.data);
            }
        }
    }
}