#include "taskSerialSend.h"


#include "struct.h"
#include "mySerial.h"
#include "taskSerialRead.h"

void serialSendThread(void *pvParameters)
{

    sPacket packet;

    while (1)
    {
        if(xQueueReceive(outSerialDataQueue, &packet, portMAX_DELAY))
        {
            serial.sendPacket((uint8_t*)&packet, sizeof(packet));
            // Serial.println("Sending packet");
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}