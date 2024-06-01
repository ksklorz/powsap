#pragma once
#include <Arduino.h>
#include "feedbackMotor.h"

class cPositionControler : public cFeedbackMotor
{
protected:
    enum eMode
    {
        eModePosition,
        eModeSpeed
    };

    float set_position;
    eMode mode;

public:
    // cFeedbackMotor motor;
    cPID controler;

    cPositionControler(float Ts, int pwm, int motA, int motB, int encA, int encB) :
        cFeedbackMotor(Ts, pwm, motA, motB, encA, encB),
        controler(Ts, -7.0, 7.0, 3.0, 0.0, 0.0), 
        set_position(0.0), mode(eModePosition)
    {};

    void setPos(float set) {mode = eModePosition, set_position = set;};
    void setSpeedMode(float set) {mode = eModeSpeed, setSpeed(set);};
    
    void update();    
};