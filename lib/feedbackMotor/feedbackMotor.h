#pragma once
#include <motor.h>
#include <encoder.h>
#include <PID.h>

class cFeedbackMotor
{
    cPID controler;
    float set_speed;
    
    public:
        cMotor mot;
        cEncoder enc;

        cFeedbackMotor(float Ts, int pwm, int motA, int motB, int encA, int encB) :
            controler(Ts, -1.0, 1.0, 0.04, .1, 0.0), set_speed(0.0), mot(pwm, motA, motB), enc(encA, encB) 
        {};

        void update();
        void setSpeed(float set) {set_speed = set;};
        float getSpeed() {return enc.omega;};
    
};