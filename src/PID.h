#pragma once
#include <Arduino.h>

/*************************************/
//
//
//                    1                      s    
// Kp  *  ( 1 +  * ------   +    Td * --------------   )
//                  Ti*s               Td/N * s + 1
//
/*************************************/

class cPID
{
    float _Ts; //czas probkowania //s

    float _outMin;
    float _outMax;

    float _Kp;
    float _Ti;
    float _Td;

    float _Nf;       //stala czasowa fitrowania czeci D: Tf=Td/N 
    float _Tt;

    float _Istate;
    float _Dstate;

    float _e1=0.0;     //roznica wejsc do wyliczenia czesci D




    float calcState(float, float);
    float calcP(float);
    float calcI(float);
    float calcD(float);

    void  saturation(float&);
    void calcAntiWindup(float, float);
    
public:

    cPID() : cPID(1.0, 0.0,0.0,1.0,0.0,0.0,10.0,0.1) {};
    cPID(float setTs, float setKp, float setTi, float setTd) : cPID(setTs, 0.0, 0.0, setKp, setTi, setTd, 10.0, 0.1) {};
    cPID(float setTs, float setOutMin, float setOutMax) : cPID(setTs, setOutMin, setOutMax, 1.0, 0.0, 0.0, 10.0, 0.1) {};
    cPID(float setTs, float setOutMin, float setOutMax, float setKp, float setTi, float setTd) : cPID(setTs, setOutMin, setOutMax, setKp, setTi, setTd, 10.0, 0.1) {};
    cPID(float setTs, float setOutMin, float setOutMax, float setKp, float setTi, float setTd, float setN, float setTt) : 
        _Ts(setTs), _outMin(setOutMin), _outMax(setOutMax), _Kp(setKp), _Ti(setTi), _Td(setTd), _Nf(setN), _Tt(setTt), _Istate(0.0), _Dstate(0.0){};

    float update(float ref, float input);

    void setIntegratorState(float I) {_Istate = I;};

    enum class param {min,max,Kp,Ti,Td,N,Tt};
    float getParam(cPID::param);
    void setParam(cPID::param, float);


};