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
            // Serial.printf("Received packet: %d; %d; %.3f\n", packet.device, packet.sensor, packet.data);
        }

        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}