#include "taskTermometer.h"
#include "config.h"
#include "termometer.h"

void taskTermometer(void *pvParameters)
{
    cTermometer termometer(PIN_TERMOMETER);
    
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        float temp = termometer.readTemperature();
        xQueueOverwrite(getTempQueue, &temp);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(PERIOD_TERMOMETER));
    }
}