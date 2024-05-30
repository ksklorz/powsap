#include "lightbulb.h"

cLightBulb::cLightBulb(uint8_t pin, uint8_t canal) :
    _pin(pin), _pwmCanal(canal)
{
    ledcSetup(_pwmCanal, 5000, _resolution); 
    ledcAttachPin(_pin, canal);

    ledcWrite(_pwmCanal, 0);
}

void cLightBulb::setBrightness(float brightness)
{
    brightness *= brightness;
    brightness = constrain(brightness, 0.0, 1.0);
    uint16_t pwmValue = static_cast<uint16_t>(brightness * ((1 << _resolution) - 1));
    ledcWrite(_pwmCanal, pwmValue);
}
