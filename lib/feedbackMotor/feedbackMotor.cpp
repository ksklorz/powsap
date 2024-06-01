#include "feedbackMotor.h"

void cFeedbackMotor::update()
{
    cEncoder::update();
    float pwm = controler.update(set_speed, omega);
    setMotor(pwm);
}