#include <Arduino.h>

#include "Config.h"


#include "taskPanel.h"
#include "taskSerial.h"

cPanelThread panel(10u);
cSerialThread serial(1000u);

void setup()
{
  // debug_init();
  Serial.begin(115200);
  delay(1000);
  panel.init();
  serial.init();
}

void loop()
{ 
  panel.update();
  serial.update();
}

