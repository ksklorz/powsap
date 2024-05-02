#include "taskHeater.h"

void cHeaterThread::setup()
{
    _termometer.init();

    _pid.setParam(cPID::param::Kp, 0.2f);
    _pid.setParam(cPID::param::Ti, 10.0f);

    _heater.setOnstate(LOW);
}

void cHeaterThread::mainLoop()
{
    float tempSet = 30.0f; 

    float tempSens = _termometer.readTemperature();

    float out = _pid.update(tempSet,tempSens);


    // Serial.print(tempSens);
    // Serial.print(" ");
    // Serial.println(out);

    _heater.setWidth(out);
    _heater.update();

}
