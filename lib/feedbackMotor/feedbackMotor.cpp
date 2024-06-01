#include "feedbackMotor.h"

void cFeedbackMotor::update()
{
    enc.update();
    float pwm = controler.update(set_speed, enc.omega);
    mot.setMotor(pwm);
}