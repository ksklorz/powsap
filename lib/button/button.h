#pragma once
#include <ezButton.h>

class cButton
{
    ezButton btn;
    void (*btnFunction)(void);

public:
    cButton(int pin) : btn(pin) {};

    void attachFunction(void (*newFunction)(void)) {btnFunction = newFunction;};

    void setup();
    void update();
};

