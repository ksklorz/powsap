#pragma once
#include <Arduino.h>


extern QueueHandle_t setLightQueue;
extern QueueHandle_t roletaSensorQueue;

void roletaThread(void *pvParameters);


static void inter();