#include <Arduino.h>

#include "taskCheckMAC.h"
void setup()
{
  Serial.begin(115200);

  xTaskCreate(
    checkMacAddressTask,
    "checkMacThread",
    4096,
    NULL,
    1,
    NULL
  );
  

  vTaskDelete(NULL);
}

void loop()
{ 
  //watek usuniety
}

