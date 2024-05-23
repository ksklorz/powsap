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
            _btnRight.attachFunction(&cPanelThread::setTemp);
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
    float tempDisp;
    switch (_state)
    {
        case eShowData:
            _display.printData(_dataIn, _dataOut);
            break;
        case eSetTemp:
            tempDisp = _potentiometer.readScaled(setTempMin, setTempMax);
            _tempData.temp = tempDisp;
            _display.printSetData(tempDisp, 1, 'C');
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

void cPanelThread::setTemp()
{
    _dataOut.temp = _tempData.temp;
    sPacket packet;
    packet.data = _tempData.temp;
    packet.time = millis();
    // _serial.sendPacket(packet);
    
    goToStateShow();
}
