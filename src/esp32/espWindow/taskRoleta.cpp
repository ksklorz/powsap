#include "taskRoleta.h"
#include "config.h"
#include "struct.h"
#include "linearServo.h"

extern QueueHandle_t setWindowQueue;

static cLinearServo roleta(2.0, 6.283,  10.0/1000.0, PIN_MOTOR_PWM, PIN_MOTOR_A, PIN_MOTOR_B, PIN_ENCODER_A, PIN_ENCODER_B);

void roletaThread(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), inter, RISING);

    float setPoint = 0.0f;
    while (1)
    {   
        sPacket packet;
        if(xQueueReceive(setWindowQueue, &packet, 0))
        {
            
            if(eSensor::eSensorWindow == packet.sensor)
            {
                setPoint = packet.data;
                // Serial.printf("Received packet\t%f\n",setPoint);
                roleta.setPerc(setPoint);
            }
        }

        roleta.update();
        // Serial.printf("%d;%.3f;%.3f;%.1f\n",millis(),roleta.getPos(), setPoint);
        vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_PERIOD_MS);
    }
}


static void inter()
{
    roleta.inter();
}