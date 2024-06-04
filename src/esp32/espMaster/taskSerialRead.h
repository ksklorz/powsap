#pragma once
#include <Arduino.h>
#include "mySerial.h"

extern QueueHandle_t inSerialDataQueue;
extern universalSerial<HardwareSerial> serial;

void serialReadThread(void *pvParameters);
