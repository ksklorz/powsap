#pragma once
#include <Arduino.h>

extern QueueHandle_t setTempQueue;
void taskControler(void *pvParameters);