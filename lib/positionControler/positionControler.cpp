#include "positionControler.h"


void cPositionControler::resetAngle(float newAngle)
{
    reset((int)(newAngle*perRev));
}

void cPositionControler::update()
{
    cFeedbackMotor::update();
    if (mode == eModePosition)
    {
        float set_speed = controler.update(set_position, getAngle());
        cFeedbackMotor::setSpeed(set_speed);
    }
}