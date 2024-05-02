#include "taskPanel.h"


void cPanelThread::setup()
{
   _display.init(); 
}

void cPanelThread::mainLoop()
{
    float pot = _potentiometer.readNorm();
    float tempRef = pot*10.0f + 15.0f;

    _display.printAllData(tempRef, 21.0f, 0.2f);
}
