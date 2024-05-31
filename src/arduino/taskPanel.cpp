#include "taskPanel.h"
#include "taskSerial.h"


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
            _btnMid.attachFunction(&cPanelThread::goToStateLight);
            _btnRight.attachFunction(&cPanelThread::goToStateWindow);
            break;
        case eSetLight:
            _btnLeft.attachFunction(&cPanelThread::goToStateShow);
            _btnMid.attachFunction(nullptr);
            _btnRight.attachFunction(&cPanelThread::setLight);
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
    float disp = 0.0f;
    switch (_state)
    {
        case eShowData:
            _display.printData(_dataIn, _dataOut);
            break;
        case eSetLight:
            disp = _potentiometer.readScaled(0.0f, 1.0f);
            if(abs(_tempData.light - disp)>0.01f;) 
                setLightContinous();
            _tempData.light = disp;
            _display.printSetData(disp*100.0f, 0, '%');
            
            break;
        case eSetTemp:
            disp = _potentiometer.readScaled(setTempMin, setTempMax);
            _tempData.temp = disp;
            _display.printSetData(disp, 1, 'C');
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

void cPanelThread::setLightContinous()
{
    _dataOut.light = _tempData.light;
    sPacket packet;

    packet.sensor = eSensorLight;
    packet.device = eDeviceLight;
    packet.data = _tempData.light;
    packet.time = millis();

    serial.sendSerial(packet);
}

void cPanelThread::setLight()
{
    setLightContinous();
    goToStateShow();
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
