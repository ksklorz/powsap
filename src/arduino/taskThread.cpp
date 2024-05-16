#include "taskThread.h"

#include <Arduino.h>

void cThread::init()
{
    _lastTime = millis();
    setup();
}

void cThread::update()
{
    unsigned long time = millis();

    if((_lastTime + _deltaTime) > time)
        return;
    

    _lastTime = time; //_lastTime+=_deltaTime; - do ewentualnej podmiany
    mainLoop();

}
