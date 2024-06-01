#ifndef gowno
#define gowno
#pragma once
#include <Arduino.h>


extern QueueHandle_t setLightQueue;

void roletaThread(void *pvParameters);


static void inter();

#endif