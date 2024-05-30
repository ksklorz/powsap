#include "taskSerialRead.h"
// #include "serialESP.h"
#include "struct.h"
// #include "taskEspNow.h"

#include "mySerial.h"

void serialReadThread(void *pvParameters)
{ 
    sPacket packet;

    universalSerial<HardwareSerial> serial(Serial0);
    serial.begin();
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.println("Serial read thread started");
    while (1)
    {
        if(serial.receivePacket((uint8_t*)&packet, sizeof(packet)))
        {
            xQueueSend(inSerialDataQueue, &packet, 0);
            Serial.println("Received packet");
            Serial.print("pT: ");
            Serial.println(packet.time);
            Serial.print("rT: ");
            Serial.println(millis());
            Serial.print("Packet device: ");
            Serial.println(packet.device);
            Serial.print("Packet sensor: ");
            Serial.println(packet.sensor);
            Serial.print("Packet data: ");
            Serial.println(packet.data);
                    
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}