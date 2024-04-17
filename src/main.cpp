#include <Arduino.h>
// #include <Arduino_FreeRTOS.h>

#include "config.h"
#include "termometer.h"
#include "display.h"
#include "potentiometer.h"
#include "PID.h"

// #include "taskControler.h"

cTermometer termometer(tempPIN);
cDisplay display;
cPotentiometer potentiometer(potPIN);
cPID heaterControler(HEATER_SAMPLE_TIME, 0.0f, 1.0f, 0.01f, 5.0f, 0.0f, 10.0f, 1.0f);

void setupThreads()
{
  // xTaskCreate(
  //   TaskControler
  //   ,  "tControler" 
  //   ,  128  
  //   ,  NULL 
  //   ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
  //   ,  NULL ); //Task Handle
}


void setup()
{
  display.init();
  termometer.init();

  // setupThreads();
}

void loop()
{
  float temp = termometer.readTemperature();
  float pot = potentiometer.readNorm();
  float tempRef = pot*10.0f + 15.0f;

  float out = heaterControler.update(tempRef, temp);

  display.printAllData(tempRef, temp, out);
  delay(1000);
}

