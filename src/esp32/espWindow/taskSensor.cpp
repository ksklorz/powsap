#include "taskSensor.h"
#include "potentiometer.h"

#include "config.h"

void sensorThread(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    cPotentiometer lightSensor(PIN_LIGHTSENSOR, 4096);

    while (1)
    {   
        float light = lightSensor.readNorm();
        xQueueOverwrite(lightSensorQueue, &light);
        vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_PERIOD_MS);
    }
}