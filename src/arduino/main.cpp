#include <Arduino.h>

#include "Config.h"


#include "taskPanel.h"
#include "taskSerial.h"

cPanelThread panel(10u);
cSerialThread serial(10u);

void setup()
{
  // debug_init();
  Serial.begin(115200);
  delay(1000);
  Serial.println("Start");
  panel.init();
  serial.init();
}

void loop()
{ 
  panel.update();
  serial.update();
}

