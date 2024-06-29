#include "taskTlm.h"

#include "taskSensor.h"
#include "taskRoleta.h"

#include "struct.h"

void tlmThread(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    while (1)
    {   
        float sensor;
        if(xQueuePeek(lightSensorQueue, &sensor, 0) == pdTRUE)
            sendSensor(sensor);

        if(xQueuePeek(roletaSensorQueue, &sensor, 0) == pdTRUE)
            sendRoleta(sensor);

        vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);
    }
}

void sendSensor(float data)
{
    sPacket packet;
    packet.sensor = eSensor::eSensorLight;
    packet.data = data;
    xQueueSend(tlmQueue, &packet, 0);
}

void sendRoleta(float data)
{
    sPacket packet;
    packet.sensor = eSensor::eSensorWindow;
    packet.data = data;
    xQueueSend(tlmQueue, &packet, 0);
}
