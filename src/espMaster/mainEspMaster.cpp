#include <Arduino.h>

#include "struct.h"
#include <HardwareSerial.h>

HardwareSerial MySerial(0);
void setup()
{
  Serial.begin(115200);
  // delay(1000);
  Serial0.begin(115200);
  delay(500);
  Serial.println("ready");
}

void loop()
{ 
  sPacket packet;
  if (Serial0.available() >= sizeof(sPacket))
  {
    uint8_t startMarker;
    bool isOk = false;
    
    Serial0.readBytes(&startMarker, 1);
    if (startMarker == 0xAA) 
    {
      Serial0.readBytes(&startMarker, 1);
      if(startMarker == 0x55)
      {
        Serial0.readBytes(((uint8_t*)&packet)+2, sizeof(packet)-2);

        Serial.printf("%d:\t", millis());
        for(int i = 0; i < sizeof(packet); i++)
        {
          Serial.printf("%02X ", ((uint8_t*)&packet)[i]);
        }
          Serial.println(sizeof(packet.status));
          
          Serial.printf("Device: %d\n", packet.device);
          Serial.printf("Status: %d\n", packet.status);
          Serial.printf("Data: %f\n", packet.data);
          Serial.printf("Time: %d\n", packet.time);
          Serial.printf("Cnt: %d\n", packet.cnt);
          Serial.printf("CRC: %d\n", packet.crc);

        // Serial.printf("%f\t%d\n",packet.data, packet.time);
      }
      else
      {
        Serial0.read();
      }
    }
    else
    {
      Serial0.read();
    }
  }

}

