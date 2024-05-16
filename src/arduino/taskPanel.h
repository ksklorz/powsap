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

enum eMachineState
{
    eShowData,
    eSetTemp,
    eSetWindow
};
class cPanelThread : public cThread 
{
    public:


private:
    cDisplay _display;
    cPotentiometer _potentiometer;
    cPanelButton _btnLeft;
    cPanelButton _btnMid;
    cPanelButton _btnRight;

    sDisplayedData _data;
    eMachineState _state;

    int _counter;
    
    void setup();
    void mainLoop();

    void test(void);
    void test2(void);



    void setupState();
    void loopState();
    void goToState(eMachineState state);

    void goToStateShow() {goToState(eShowData);};
    void goToStateTemp() {goToState(eSetTemp);};
    void goToStateWindow() {goToState(eSetWindow);};

    public:
        cPanelThread(uint32_t dT) : cThread(dT), _potentiometer(potPIN), 
        _btnLeft(btnLeftPIN, this), _btnMid(btnMidPIN, this), _btnRight(btnRightPIN, this), 
        _state(eShowData), _counter(0) {};

};


