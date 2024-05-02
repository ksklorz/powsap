#include <Arduino.h>
// #include <Arduino_FreeRTOS.h>

// #include "avr8-stub.h"
// #include "app_api.h"

#include "config.h"

// #include "termometer.h"
// #include "display.h"
// #include "potentiometer.h"
// #include "PID.h"

// #include "taskControler.h"

#include "taskPanel.h"
#include "taskHeater.h"

cPanelThread panel(10u);
cHeaterThread heater(10u);

// cTermometer termometer(tempPIN);
// cPID heaterControler(HEATER_SAMPLE_TIME, 0.0f, 1.0f, 0.01f, 5.0f, 0.0f, 10.0f, 1.0f);

void setup()
{
  // debug_init();
  Serial.begin(115200);
  delay(1000);
  panel.init();
  heater.init();

}

void loop()
{ 

  panel.update();
  heater.update();
}

