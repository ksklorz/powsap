#pragma once
#include <Arduino.h>


extern QueueHandle_t lightSensorQueue;

void sensorThread(void *pvParameters);
