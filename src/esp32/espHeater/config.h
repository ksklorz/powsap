#pragma once
#include <arduino.h>

const uint8_t PIN_RELAY = 8;
const uint8_t PIN_TERMOMETER = 10;


const uint16_t PERIOD_PWM = 5; //5ms * 1000 = 10s
const uint16_t PERIOD_TERMOMETER = 2000; //2s
const uint16_t PERIOD_CONTROLER = 2000; //10s
const uint16_t PERIOD_TLM = 5000; //1s