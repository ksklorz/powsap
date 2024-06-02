#include <Arduino.h>
#include "taskEspNow.h"
#include "taskPWM.h"
#include "taskTermometer.h"
#include "taskControler.h"
#include "taskPWM.h"

#include "taskTest.h"
QueueHandle_t testQueue;

QueueHandle_t inDataQueue;
QueueHandle_t outDataQueue;

QueueHandle_t setPWMQueue;
QueueHandle_t getTempQueue;


void setup()
{
  Serial.begin(115200);

  inDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
  outDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));

  setPWMQueue = xQueueCreate(1, sizeof(float));
  getTempQueue = xQueueCreate(1, sizeof(float));
  
  testQueue = inDataQueue;

  xTaskCreate(
    taskPWM,
    "taskPWM",
    4096,
    NULL,
    10,
    NULL
  );
  xTaskCreate(
    taskTermometer,
    "taskTermometer",
    4096,
    NULL,
    4,
    NULL
  );
  xTaskCreate(
    taskControler,
    "taskControler",
    4096,
    NULL,
    3,
    NULL
  );

  xTaskCreate(
    espNowThread,
    "espNowThread",
    4096,
    NULL,
    5,
    NULL
  );

  // xTaskCreate(
  //   testThread,
  //   "testThread",
  //   4096,
  //   NULL,
  //   1,
  //   NULL
  // );
 

  vTaskDelete(NULL);

}

void loop()
{ 
  //watek usuniety
}

