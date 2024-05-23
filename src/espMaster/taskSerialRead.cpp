#include "taskSerialRead.h"
#include "serialESP.h"

void serialReadThread(void *pvParameters)
{ 
    cSerialESP serial;
    serial.begin();
    sPacket packet;

    while (1)
    {
        if(serial.receivePacket(packet))
        {
            Serial.print("Received packet: ");
            Serial.print(packet.data);
            Serial.print(" ");
            Serial.print(packet.time);
            Serial.print(" ");
            Serial.println(packet.crc);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}