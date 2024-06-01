#include "taskRoleta.h"
// #include "config.h"
#include "struct.h"

#include "motor.h"
#include "encoder.h"
#include "feedbackMotor.h"

extern QueueHandle_t setWindowQueue;

// static cEncoder motorEncoder(PIN_ENCODER_A, PIN_ENCODER_B);
static cFeedbackMotor motor(10.0/1000.0, PIN_MOTOR_PWM, PIN_MOTOR_A, PIN_MOTOR_B, PIN_ENCODER_A, PIN_ENCODER_B);

void roletaThread(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    // cMotor motor(PIN_MOTOR_PWM, PIN_MOTOR_A, PIN_MOTOR_B);
    
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), inter, RISING);

    float setPoint = 0.0f;
    int i = 0;

    while (1)
    {   
        sPacket packet;
        if(xQueueReceive(setWindowQueue, &packet, 0))
        {
            if(eSensor::eSensorWindow == packet.sensor)
            {
                setPoint = packet.data*10.0f;
                motor.setSpeed(setPoint);
            }
        }

        

        ++i;
        motor.update();
        // if(i > 10)
        // {
            i = 0;
            Serial.printf("%d;%.3f;%.3f;%.1f\n",millis(),motor.enc.omega,motor.enc.getPos(), setPoint);
        // }
        vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_PERIOD_MS);
    }
}


static void inter()
{
    motor.enc.inter();
}