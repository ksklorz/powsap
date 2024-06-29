#pragma once
#include <Arduino.h>


extern QueueHandle_t tlmQueue;
void tlmThread(void *pvParameters);

void sendRoleta(float data);
void sendSensor(float data);
