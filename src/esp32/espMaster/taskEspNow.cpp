#include "taskEspNow.h"

#include "Wifi.h"
#include "esp_now.h"
#include "MACdata.h"


// #include "freertos/queue.h"





void espNowThread(void *pvParameters)
{

    WiFi.mode(WIFI_STA);
    while(esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

    while(true)
    {
        sPacket packet;
        if(xQueueReceive(outDataQueue, &packet, 0))
        {
            esp_now_send(getMac(packet.device), (uint8_t*)&packet, sizeof(sPacket));
        }
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void espNowReceiver(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    sPacket packet;
    memcpy(&packet, incomingData, sizeof(sPacket));
    xQueueSend(inDataQueue, &packet, 0);
}

uint8_t *getMac(eDevice device)
{
    for(auto &it : MACmap)
    {
        if(it.first == device)
        {
            return it.second.mac;
        }
    }
    return nullptr;
}
