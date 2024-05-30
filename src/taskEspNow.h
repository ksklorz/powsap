#pragma once
#include <Arduino.h>
#include "struct.h"

#define QUEUE_SIZE 10

#ifdef ARDUINO_ARCH_ESP32

extern QueueHandle_t inDataQueue;
extern QueueHandle_t outDataQueue;


void espNowThread(void *pvParameters);

void espNowReceiver(const uint8_t * mac, const uint8_t *incomingData, int len);
uint8_t* getMac(eDevice device);

#endif
