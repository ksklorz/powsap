#ifdef ARDUINO_ARCH_ESP32

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
    esp_now_register_recv_cb(espNowReceiver);

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, getMac(eDevice::eDeviceLight), 6);

    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    while (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Error adding peer");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

    while(true)
    {
        sPacket packet;
        

        if(xQueueReceive(outDataQueue, &packet, portMAX_DELAY))
        {
            sMACaddress mac;
            memcpy(mac.mac, getMac(packet.device),6);
            esp_err_t result = esp_now_send(mac.mac, (uint8_t*)&packet, sizeof(sPacket));
            
            Serial.println(packet.data);
            // Serial.println(packet.device);
            Serial.println(result, HEX);
            Serial.println();
            
        }
        // vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void espNowReceiver(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    sPacket packet;
    memcpy(&packet, incomingData, sizeof(sPacket));
    xQueueSend(inDataQueue, &packet, 0);
    Serial.println("Received packet");
    Serial.println(packet.data);
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

#endif
