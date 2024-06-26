#include "linearServo.h"

void cLinearServo::resetPos(float position)
{
    resetAngle(position*gear_ratio/(2.0*PI));
}