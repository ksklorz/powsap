#pragma once
#include <Arduino.h>


extern QueueHandle_t tlmQueue;
void taskTelemetry(void *pvParameters);