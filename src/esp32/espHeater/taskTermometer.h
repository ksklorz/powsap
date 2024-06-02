#pragma once
#include <Arduino.h>

extern QueueHandle_t getTempQueue;
void taskTermometer(void *pvParameters);