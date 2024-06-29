#pragma once
#include <motor.h>
#include <encoder.h>
#include <PID.h>

class cFeedbackMotor : public cMotor, public cEncoder
{
    cPID controler;
    float set_speed;
    
    public:
        // cMotor mot;
        // cEncoder enc;

        cFeedbackMotor(float Ts, int pwm, int motA, int motB, int encA, int encB) :
            cMotor(pwm, motA, motB), cEncoder(encA, encB),
            controler(Ts, -1.0, 1.0, 0.03, .1, 0.0), set_speed(0.0)
        {};

        void update();
        void setSpeed(float set) {set_speed = set;};
        float getSpeed() {return omega;};
    
};