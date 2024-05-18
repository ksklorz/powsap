#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Wire.h"

class cDisplay
{
protected:
    Adafruit_SSD1306 _display;

public:
    void init();
    void printAllData(float tempSet, float tempGet, float out);

    void printTest(int x);
    void printSetData(float data, float d, char unit);
};


