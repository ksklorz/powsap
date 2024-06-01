#pragma once
#include "positionControler.h"

class cLinearServo : public cPositionControler
{
    float max_position;
    float gear_ratio; // rev/m

public:
    cLinearServo(float setMax, float setGear, float Ts, int pwm, int motA, int motB, int encA, int encB) :
        max_position(setMax), gear_ratio(setGear),
        cPositionControler(Ts, pwm, motA, motB, encA, encB)
    {};
        
    void setPos(float set) {cPositionControler::setPos(set*gear_ratio);};
    void setPerc(float perc) {setPos(perc*max_position);};

};