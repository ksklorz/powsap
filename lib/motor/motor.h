#pragma once
#include <Arduino.h>

class cMotor
{
private:
    int freq = 10000;
    int res = 8;
    int PWMChannel = 0;
    static int channelsCount;

    int pwmPIN;
    int AoutPIN;
    int BoutPIN;
    void initMotor(int PWM, int A, int B);

    void setSpeed(float set);
    void setDir(int dir);

public:
    cMotor(int PWM, int A, int B) : pwmPIN(PWM), AoutPIN(A), BoutPIN(B) {initMotor(PWM,A,B);};
    void setMotor(float set);
};