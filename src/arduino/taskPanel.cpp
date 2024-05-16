#include "taskPanel.h"

void cPanelThread::setup()
{
   _display.init(); 
   _btnLeft.setup();
   _btnMid.setup();
   _btnRight.setup();

    _display.printTest(21);
    setupState();
}

void cPanelThread::mainLoop()
{
    loopState();
    _btnLeft.update();
    _btnMid.update();
    _btnRight.update();

}

void cPanelThread::test()
{
    Serial.println(13);
    _display.printTest(13);
}

void cPanelThread::test2()
{
    Serial.println(5);
    _display.printTest(5);
}

void cPanelThread::setupState()
{   
    switch(_state)
    {
        case eShowData:
            _btnLeft.attachFunction(&cPanelThread::goToStateTemp);
            _btnMid.attachFunction(nullptr);
            _btnRight.attachFunction(&cPanelThread::goToStateWindow);
            break;
        case eSetTemp:
            _btnLeft.attachFunction(&cPanelThread::goToStateShow);
            _btnMid.attachFunction(nullptr);
            _btnRight.attachFunction(nullptr);
            break;
        case eSetWindow:
            _btnLeft.attachFunction(&cPanelThread::goToStateShow);
            _btnMid.attachFunction(nullptr);
            _btnRight.attachFunction(nullptr);
            break;
    }
}

void cPanelThread::loopState()
{
    switch (_state)
    {
        case eShowData:
            _display.printTest(999);
            break;
        case eSetTemp:
            _display.printTest((int)(_potentiometer.readNorm()*100));
            break;
        case eSetWindow:
            _display.printTest((int)(_potentiometer.readNorm()*500));
            break;
    }
}

void cPanelThread::goToState(eMachineState state)
{
    _state = state;
    setupState();
}
