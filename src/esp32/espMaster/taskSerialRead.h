#pragma once
#include <Arduino.h>

extern QueueHandle_t inSerialDataQueue;

void serialReadThread(void *pvParameters);
