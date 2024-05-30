#include <Arduino.h>

#include "taskSerialRead.h"
#include "taskEspNow.h"
#include "taskCheckMAC.h"

#include "taskTest.h"

// #include "struct.h"
// #include <HardwareSerial.h>

QueueHandle_t inDataQueue;
QueueHandle_t outDataQueue;
QueueHandle_t outSerialDataQueue;
QueueHandle_t inSerialDataQueue;

QueueHandle_t testQueue;

// HardwareSerial MySerial(0);
void setup()
{
  Serial.begin(115200);
  delay(2000);

    inDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
    outDataQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
    outSerialDataQueue = inDataQueue;
    inSerialDataQueue = outDataQueue;

    testQueue = xQueueCreate(QUEUE_SIZE, sizeof(sPacket));
    outDataQueue = testQueue;


  xTaskCreate(
    serialReadThread,
    "serialReadThread",
    4096,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    espNowThread,
    "espNowThread",
    4096,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    testThread,
    "testThread",
    4096,
    NULL,
    1,
    NULL);

  // xTaskCreate(
  //   checkMacAddressTask,
  //   "checkMacThread",
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

