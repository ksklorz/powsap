#pragma once
#include <Arduino.h>


extern QueueHandle_t setLightQueue;

void lightBulbThread(void *pvParameters);
