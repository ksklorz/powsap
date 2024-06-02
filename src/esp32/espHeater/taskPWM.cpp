#include "taskPWM.h"

#include "relay.h"
#include "config.h"

void taskPWM(void *pvParameters)
{

    cRelay relay(PIN_RELAY);
    
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        float newWidth = 0.0f;
        if(xQueueReceive(setPWMQueue, &newWidth, 0) == pdTRUE)
        {
            relay.setWidth(newWidth);
        }

        relay.update();
        vTaskDelayUntil(&xLastWakeTime, PERIOD_PWM / portTICK_PERIOD_MS);
    }
}