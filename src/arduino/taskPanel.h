#pragma once
#include "taskThread.h"

#include <Arduino.h>

#include "config.h"
#include "display.h"
#include "potentiometer.h"
#include "PanelButton.h"



struct sDisplayedData
{
    float temp = 0.0f;
    float pot = 0.0f;
};

class cPanelThread : public cThread 
{
    cDisplay _display;
    cPotentiometer _potentiometer;
    cPanelButton _btnLeft;
    cPanelButton _btnMid;
    cPanelButton _btnRight;

    sDisplayedData _data;

    int _counter;
    
    void setup();
    void mainLoop();

    void test(void);
    void test2(void);

    public:
        cPanelThread(uint32_t dT) : cThread(dT), _potentiometer(potPIN), 
        _btnLeft(btnLeftPIN, this), _btnMid(btnMidPIN, this), _btnRight(btnRightPIN, this), _counter(0) {};

};


