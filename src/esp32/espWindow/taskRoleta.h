#ifndef gowno
#define gowno
#pragma once
#include <Arduino.h>
#include "encoder.h"
#include "config.h"


extern QueueHandle_t setLightQueue;

void roletaThread(void *pvParameters);


static void inter();

#endif