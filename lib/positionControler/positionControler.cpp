#include "positionControler.h"

void cPositionControler::update()
{
    cFeedbackMotor::update();
    if (mode == eModePosition)
    {
        float set_speed = controler.update(set_position, getPos());
        setSpeed(set_speed);
    }
}