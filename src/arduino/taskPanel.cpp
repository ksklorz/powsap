#include "taskPanel.h"



void cPanelThread::setup()
{
   _display.init(); 
   _btnLeft.setup();
   _btnMid.setup();
   _btnRight.setup();

    _display.printTest(21);
   _btnLeft.attachFunction(&cPanelThread::test);
   _btnRight.attachFunction(&cPanelThread::test2);
}

void cPanelThread::mainLoop()
{
    _btnLeft.update();
   _btnMid.update();
   _btnRight.update();
    // float pot = _potentiometer.readNorm();
    
    // float last = _data.temp;
    // _data.temp = pot*10.0f + 15.0f; 

    // if(last!= _data.temp)
    //     _display.printAllData(_data.temp, 21.0f, 0.2f);
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


