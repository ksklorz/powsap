#pragma once 
#include <ezButton.h>
// #include "taskPanel.h"

class cPanelThread;

class cPanelButton// : public cButton
{
    ezButton _btn;
    cPanelThread* _obj;
    void (cPanelThread::*btnFunction)(void);

public:
    cPanelButton(int pin, cPanelThread* obj) : _btn(pin), _obj(obj){};

    void attachFunction(void (cPanelThread::*newFunction)(void)) {btnFunction = newFunction;};

    void setup();
    void update();
};