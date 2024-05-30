#include <Arduino.h>
#include "taskCheckMAC.h"
#include "struct.h"
#include "taskLight.h"
#include "taskEspNow.h"
//#include "taskTest.h"

QueueHandle_t setLightQueue;
QueueHandle_t inDataQueue;
QueueHandle_t outDataQueue;



void setup()
{
  Serial.begin(115200);

  inDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
  outDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));

  setLightQueue = inDataQueue;

  xTaskCreate(
    lightBulbThread,
    "lightBulbThread",
    4096,
    NULL,
    5,
    NULL
  );

  xTaskCreate(
    espNowThread,
    "espNowThread",
    4096,
    NULL,
    4,
    NULL
  );
 

  vTaskDelete(NULL);
}

void loop()
{ 
  //watek usuniety
}

