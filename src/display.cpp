#include "display.h"



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C // Wokwi uzywa ponoc 0x3c

void cDisplay::init() 
{  
    _display=Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    _display.begin(SSD1306_SWITCHCAPVCC,SCREEN_ADDRESS);
    _display.clearDisplay();
}

void cDisplay::printAllData(float tempSet, float tempGet, float out)
{
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(WHITE); 
    _display.setCursor(0,0);
    _display.print(tempSet,1);
    _display.println("C  ");
    _display.print(tempGet,1);
    _display.println("C");
    _display.print(100.0f*out,0);
    _display.println("%  ");
    

    _display.display();
}