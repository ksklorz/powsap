#pragma once
#include "positionControler.h"

class cLinearServo : public cPositionControler
{
    float max_position;
    float gear_ratio; // rad/m

public:
    cLinearServo(float setMax, float setGear, float Ts, int pwm, int motA, int motB, int encA, int encB) :
        max_position(setMax), gear_ratio(setGear * 2.0 * PI),
        cPositionControler(Ts, pwm, motA, motB, encA, encB)
    {};
    
    float getPos() {return cPositionControler::getAngle()/gear_ratio;};
    void setPos(float set) {cPositionControler::setAngle(set*gear_ratio);};
    void setPerc(float perc) {setPos(perc*max_position);};
    void setSpeed(float speed) {cPositionControler::setSpeed(speed*gear_ratio);};
    void resetPos() {cEncoder::reset();};
    void resetPos(float position);
    
};