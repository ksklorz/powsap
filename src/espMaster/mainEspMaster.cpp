#include <Arduino.h>

#include "taskSerialRead.h"
// #include "struct.h"
// #include <HardwareSerial.h>

HardwareSerial MySerial(0);
void setup()
{
  Serial.begin(115200);

  xTaskCreate(
    serialReadThread,
    "serialReadThread",
    4096,
    NULL,
    1,
    NULL
  );
  
}

void loop()
{ }

