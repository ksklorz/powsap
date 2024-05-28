#pragma once
#include <Arduino.h>

extern QueueHandle_t outSerialDataQueue;

void serialSendThread(void *pvParameters);
