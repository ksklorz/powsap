#pragma once
#include <arduino.h>

const uint8_t PIN_RELAY = 8;
const uint8_t PIN_FAN = 6;
const uint8_t PIN_TERMOMETER = 10;


const uint16_t PERIOD_PWM = 5; //5ms * 1000 = 5s
const uint16_t PERIOD_TERMOMETER = 1000; //2s
const uint16_t PERIOD_CONTROLER = 5000; //10s
const uint16_t PERIOD_TLM = 5000; //1s