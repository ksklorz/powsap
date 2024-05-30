#include "taskSerialSend.h"


#include "struct.h"
#include "mySerial.h"

void serialSendThread(void *pvParameters)
{
    universalSerial<HardwareSerial> serial(Serial0);
    serial.begin();
    sPacket packet;

    while (1)
    {
        if(xQueueReceive(outSerialDataQueue, &packet, portMAX_DELAY))
        {
            serial.sendPacket((uint8_t*)&packet, sizeof(packet));
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}