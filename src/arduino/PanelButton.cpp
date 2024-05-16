#include "PanelButton.h"
#include "taskPanel.h"

void cPanelButton::setup()
{
    static const int timeDebounce = 50;
    _btn.setDebounceTime(timeDebounce);
}

void cPanelButton::update()
{
    _btn.loop();

    if(_btn.isPressed())
    {
        _btn.loop();
        if(nullptr != btnFunction)
            (_obj->*btnFunction)();
    }
}