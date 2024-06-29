#include <Arduino.h>
#include "taskCheckMAC.h"
#include "struct.h"
#include "taskRoleta.h"
#include "taskEspNow.h"
#include "taskSensor.h"
#include "taskTlm.h"

#include "taskTest.h"
QueueHandle_t testQueue;


QueueHandle_t setWindowQueue;
QueueHandle_t inDataQueue;
QueueHandle_t outDataQueue;
QueueHandle_t lightSensorQueue;
QueueHandle_t roletaSensorQueue;
QueueHandle_t tlmQueue;

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(1);

  inDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
  outDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));

  setWindowQueue = inDataQueue;
  testQueue = inDataQueue;

  lightSensorQueue = xQueueCreate(1, sizeof(float));
  roletaSensorQueue = xQueueCreate(1, sizeof(float));

  tlmQueue = outDataQueue;

  xTaskCreate(
    roletaThread,
    "roletaThread",
    4096,
    NULL,
    4,
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

  xTaskCreate(
    sensorThread,
    "sensorThread",
    4096,
    NULL,
    3,
    NULL
  );

  xTaskCreate(
    tlmThread,
    "tlmThread",
    4096,
    NULL,
    2,
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

