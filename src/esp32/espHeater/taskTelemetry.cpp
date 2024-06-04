#include "taskTelemetry.h"

#include "config.h"
#include "struct.h"
#include "taskTermometer.h"

void taskTelemetry(void *pvParameters)
{
    


    float measuredTemp = 20.0f;

    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    sPacket packet;

    while(true)
    {
        xQueuePeek(getTempQueue, &measuredTemp, 0);

        packet.device = eDevice::eDeviceMaster;
        packet.data = measuredTemp;
        packet.time = millis();
        packet.sensor = eSensor::eSensorTemp;

        xQueueSend(tlmQueue, &packet, 0);

        xTaskDelayUntil(&xLastWakeTime, PERIOD_TLM/ portTICK_PERIOD_MS);
    }
}