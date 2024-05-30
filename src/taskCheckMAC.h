#include <Arduino.h>
#include <WiFi.h>

#ifdef ARDUINO_ARCH_ESP32


void checkMacAddressTask(void *parameter) {
    while (1) {
        uint8_t mac[6];
        esp_read_mac(mac, ESP_MAC_WIFI_STA);

        Serial.print("MAC Address: {0x");
        for (int i = 0; i < 6; i++) {
            Serial.print(mac[i], HEX);
            if (i < 5) {
                Serial.print(" ,0x");
            }
        }
        Serial.println("}");

        vTaskDelay(pdMS_TO_TICKS(5000)); // Czekaj 5 sekund
    }
}



#endif