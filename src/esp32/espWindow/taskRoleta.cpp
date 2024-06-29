#include "taskRoleta.h"
#include "config.h"
#include "struct.h"
#include "linearServo.h"
#include "taskSensor.h"

extern QueueHandle_t setWindowQueue;

static cLinearServo roleta(12.0f, 1.0f/12.5f,  (float)deltaTime/1000.0, PIN_MOTOR_PWM, PIN_MOTOR_A, PIN_MOTOR_B, PIN_ENCODER_A, PIN_ENCODER_B);

void roletaThread(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), inter, RISING);
    pinMode(PIN_CALIB, INPUT_PULLUP);

    float setPoint = 0.0f;
    bool autoMode = false;

    roleta.setSpeed(5.0f);
    while(digitalRead(PIN_CALIB))
    {
        roleta.update();
        vTaskDelayUntil(&xLastWakeTime, deltaTime / portTICK_PERIOD_MS);
    }
    
    roleta.setSpeed(-5.0f);
    while(!digitalRead(PIN_CALIB))
    {
        roleta.update();
        vTaskDelayUntil(&xLastWakeTime, deltaTime / portTICK_PERIOD_MS);
    }

    roleta.setSpeed(1.0f);
    while(digitalRead(PIN_CALIB))
    {
        roleta.update();
        vTaskDelayUntil(&xLastWakeTime, deltaTime / portTICK_PERIOD_MS);
    }

    roleta.setPerc(0.0f);
    roleta.resetPos(6.0f);

    while (1)
    {   
        
        sPacket packet;
        while(xQueueReceive(setWindowQueue, &packet, 0))
        {
            
            if(eSensor::eSensorWindow == packet.sensor)
            {
                setPoint = packet.data;
                
                if (setPoint < 0.0f)
                    autoMode = true;
                else
                    autoMode = false;
                    //nie mam sily robic tego porzadnie
                // Serial.printf("Received packet\t%f\n",setPoint);
                roleta.setPerc(setPoint);
            }
            Serial.println(roleta.getPos());
        }
        
        if(autoMode)
            if(xQueuePeek(lightSensorQueue, &setPoint, 0) == pdTRUE)
                roleta.setPerc(setPoint);
            
        


        roleta.update();
        float pos = roleta.getPerc();
        xQueueOverwrite(roletaSensorQueue, &pos);

        // Serial.printf("%d;%.3f;%.3f;%.1f\n",millis(),roleta.getPos(), setPoint);
        vTaskDelayUntil(&xLastWakeTime, deltaTime / portTICK_PERIOD_MS);
    }
}


static void inter()
{
    roleta.inter();
}