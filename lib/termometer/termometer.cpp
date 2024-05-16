#include "termometer.h"

//funkcja inicjalizujaca temrometr
void cTermometer::init()
{
    _sensor.begin();
    _sensor.setWaitForConversion(false);
}

//funkcja odczytujaca aktualną temperature
float cTermometer::readTemperature()
{
    
    _sensor.requestTemperatures();
    //jakikolwiek czujnik jes podlaczony
    float temp = _sensor.getTempCByIndex(0);     

    return temp;
}
