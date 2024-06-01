#include "encoder.h"

void cEncoder::inter()
{
    int b = digitalRead(pinB);
    if(b)
        ++pos;
    else
        --pos;
}

void cEncoder::update()
{
  int time = millis();
  float diffTime = (float)(time - lastTime)/1000.0;
  int diffPos = pos - lastPos;

    if(diffTime == 0.0)
        return;

  lastTime = time;
  lastPos = pos;

  float omegaNF = (float)diffPos/diffTime;

  omegaNF /= perRev;
  omegaNF *= 2.0 * PI;
  
  //lowpass filter
  static const float tau = 0.01; //stala czasowa
  float a = tau/(tau + diffTime);
  omega = a * omega + (1.0-a) * omegaNF; 
}

void cEncoder::reset()
{
    pos = 0;
    omega = 0.0f;
    lastPos = 0;
    lastTime = millis();
}

float cEncoder::getPos()
{
    return (float)pos /perRev * 2.0 * PI;
}