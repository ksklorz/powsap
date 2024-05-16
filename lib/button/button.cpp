#include "button.h"

static const int timeDebounce = 50;

void cButton::setup()
{
    btn.setDebounceTime(timeDebounce);
}

void cButton::update()
{
    btn.loop();

    if(btn.isPressed())
    {
        btn.loop();
        if(nullptr != btnFunction)
            (*btnFunction)();
    }
}
