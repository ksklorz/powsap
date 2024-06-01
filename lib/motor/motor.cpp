#include "motor.h"

int cMotor::channelsCount = 0;

void cMotor::initMotor(int PWM, int A, int B)
{
    PWMChannel = channelsCount;
    ++channelsCount;
    ledcSetup(PWMChannel, freq, res);
    ledcAttachPin(pwmPIN,PWMChannel);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
}

void cMotor::setSpeed(float set)
{
    int dutyCycle;

    set = constrain(set,0.0f,1.0f);
    dutyCycle = (int)(set*255.0f);
    ledcWrite(PWMChannel,dutyCycle);
}

void cMotor::setDir(int dir)
{
    if(dir == 0)
    {
        digitalWrite(AoutPIN,LOW);
        digitalWrite(BoutPIN,LOW);
        return;
    } 
    else if(dir > 0)
    {
        digitalWrite(AoutPIN,HIGH);
        digitalWrite(BoutPIN,LOW);
        return;
    }
    else if(dir < 0)
    {
        digitalWrite(AoutPIN,LOW);
        digitalWrite(BoutPIN,HIGH);
        return;
    }
}

void cMotor::setMotor(float set)
{
    set = constrain(set,-1.0f,1.0f);
    if(fabs(set)<0.01)
    {
        setDir(1);
        setSpeed(fabs(set));
        return;
    } 

    setSpeed(fabs(set));
    int dir;
    dir = (set > 0) - (set < 0);
    setDir(dir);

}