#include "PID.h"

float cPID::calcState(float Ref, float In)
{
	float e, P, I, D;
	const float eps = 0.000001;
	float out;

	e = Ref - In;

	P = calcP(e);
	I = (fabs(_Ti) > eps) ? calcI(e): 0.0;
	D = (fabs(_Td) > eps) ? calcD(e) : 0.0;

	out = P + I + D;

	float preSat = out; //do ew. wyliczania anti-windup
	saturation(out);

	if (fabs(_Ti) > eps)    //jeżeli całka jest wyłączona to anti-windup też nie działa
		if (fabs(_Tt) > eps)
			calcAntiWindup(preSat, out);

	if (out != out)  //sprawdzenie czy nie jest NaN
		out = 0.0;
	
	return out;

}

float cPID::calcP(float e)
{
	return e*_Kp;
}

float cPID::calcI(float e)
{
	_Istate += _Kp * _Ts / _Ti * e;
	if (_Istate != _Istate)
		_Istate = 0.0;
	return _Istate;
}

//e - aktualny uchyb
//Ts - próbkowanie regulatora
//wyjscie: stan członu D regulatora
float cPID::calcD(float e)
{
	float dE;	// różnica uchybów od poprzedniej próbki
	float D;	// wyjście części D
	float Tf = _Td / _Nf; // stała czasowa filtrowania

	dE = e - _e1;
	D = _Kp * _Td * dE;
	D += _Dstate * (Tf - _Ts/2.0);
	D /= (Tf + _Ts/2.0);

	_e1 = e; //zapamiętanie błędu
	_Dstate = D; //zapamiętanie stanu wyjścia

	return D;
}

void cPID::saturation(float &out)
{
	if (out < _outMin)
		out = _outMin;

	if (out > _outMax)
		out = _outMax;
}

void cPID::calcAntiWindup(float preSat, float postSat)
{
	if(_Tt!=0.0)//podwójne zabezpiecznie
		_Istate -= (preSat-postSat)/_Tt * _Ts;
}


float cPID::update(float ref, float input)
{
    return calcState(ref, input);
}

float cPID::getParam(cPID::param param)
{
	float res = 0.0;

	switch (param)
	{
	case cPID::param::min:
		res = _outMin;
		break;
	case cPID::param::max:
		res = _outMax;
		break;
	case cPID::param::Kp:
		res = _Kp;
		break;
	case cPID::param::Ti:
		res = _Ti;
		break;
	case cPID::param::Td:
		res = _Td;
		break;
	case cPID::param::N:
		res = _Nf;
		break;
	case cPID::param::Tt:
		res = _Tt;
		break;
	}

	return res;
}

void cPID::setParam(cPID::param param, float set)
{

	switch (param)
	{
	case cPID::param::min:
		_outMin=set;
		break;
	case cPID::param::max:
		_outMax = set;
		break;
	case cPID::param::Kp:
		_Kp =set;
		break;
	case cPID::param::Ti:
		_Ti = set;
		break;
	case cPID::param::Td:
		_Td = set;
		break;
	case cPID::param::N:
		_Nf = set;
		break;
	case cPID::param::Tt:
		_Tt = set;
		break;
	}

}