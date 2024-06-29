#include "taskControler.h"

#include "config.h"
#include "PID.h"

#include "taskTermometer.h"
#include "taskPWM.h"
#include "struct.h"

void taskControler(void *pvParameters)
{
    float measuredTemp = 20.0f;
    float setTemp = 15.0f;

    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    cPID controler((float)PERIOD_CONTROLER / 1000.0f, 0.0f, 1.0f, 1.0f, 410.0f, 0.0f, 10.0f, 200.0f);
    pinMode(PIN_FAN, OUTPUT);

    vTaskDelay(100);
    digitalWrite(PIN_FAN, HIGH);
    vTaskDelay(100);


    while(true)
    {
        sPacket temp;
        if(xQueueReceive(setTempQueue, &temp, 0) == pdTRUE)
        {
            if(temp.sensor == eSensor::eSensorTemp)
                setTemp = temp.data;
        }

        if(xQueuePeek(getTempQueue, &measuredTemp, 0) == pdTRUE)
        {
            float out = controler.update(setTemp, measuredTemp);
            xQueueOverwrite(setPWMQueue, &out);
            // Serial.printf("%d;%f;%f;%f\n", millis(), setTemp, measuredTemp, out);
        }

        // Serial.printf("Measured: %.2f\tSet: %.2f\tOutput: %.2f\n", measuredTemp, setTemp, out);
        // Serial.printf("%d;%f;%f\n", millis(), measuredTemp, out);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(PERIOD_CONTROLER));
    }
}