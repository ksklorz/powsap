#pragma once
#include <Arduino.h>

extern QueueHandle_t setPWMQueue;
void taskPWM(void *pvParameters);