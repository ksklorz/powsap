#include <Arduino.h>

#include "config.h"


#include "taskPanel.h"

cPanelThread panel(10u);

void setup()
{
  // debug_init();
  Serial.begin(115200);
  delay(1000);
  panel.init();
}

void loop()
{ 
  panel.update();
}

