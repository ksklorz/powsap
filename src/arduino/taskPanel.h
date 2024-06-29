#pragma once
#include "taskThread.h"

#include <Arduino.h>

#include "config.h"
#include "PanelDisplay.h"
#include "potentiometer.h"
#include "PanelButton.h"

#include "struct.h"

enum eMachineState
{
    eShowData,
    eSetLight,
    eSetWindow,
    eSetTemp
};
class cPanelThread : public cThread 
{

private:
    cPanelDisplay _display;
    cPotentiometer _potentiometer;
    cPanelButton _btnLeft;
    cPanelButton _btnMid;
    cPanelButton _btnRight;

    eMachineState _state;

    sDataCmd _dataIn;
    sDataCmd _dataOut;
    sDataCmd _tempData;

    // cSerialArd _serial;

    int _counter;
    
    void setup();
    void mainLoop();

    void test(void);
    void test2(void);



    void setupState();
    void loopState();
    void goToState(eMachineState state);

    void goToStateShow() {goToState(eShowData);};
    void goToStateLight() {goToState(eSetLight);}
    void goToStateTemp() {goToState(eSetTemp);};
    void goToStateWindow() {goToState(eSetWindow);}
    void setLightContinous();
    void setLight();
    void setTemp();

    void setWindowContinous();
    void setWindow();
    void setWindowAuto();

    public:
        cPanelThread(uint32_t dT) : cThread(dT), _potentiometer(potPIN), 
        _btnLeft(btnLeftPIN, this), _btnMid(btnMidPIN, this), _btnRight(btnRightPIN, this), 
        _state(eShowData), _counter(0) {};

        void newSensorData(sPacket packet);

};


