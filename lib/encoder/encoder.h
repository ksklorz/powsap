#pragma once
#include "arduino.h"

class cEncoder
{

    int lastPos;
    int lastTime;

    protected:
    const float perRev = 960.0;

    public:
        int pinA;
        int pinB;

        int pos;
        float omega;

        cEncoder(int A, int B) : pinA(A), pinB(B), pos(0), omega(0.0), lastPos(0) {pinMode(pinA, INPUT); pinMode(pinB, INPUT); lastTime = millis();};

        void inter();
        void update();
        void reset();
        void reset(int newPos);

        float getAngle();
};

