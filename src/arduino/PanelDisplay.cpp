#include "PanelDisplay.h"

void cPanelDisplay::printData(sDataCmd dataIn, sDataCmd dataOut)
{
    _display.clearDisplay();
    _display.setTextSize(1);
    //_display.setTextColor(WHITE);
    _display.setCursor(0,0);
    _display.print("Tout:");
    _display.print(dataOut.temp,1);
    _display.print("C\t");
    _display.print("Tin:");
    _display.print(dataIn.temp,1);
    _display.print("C\n");

    _display.print("Wout:");
    _display.print(dataOut.window,0);
    _display.print("%\t");
    _display.print("Win:");
    _display.print(dataIn.light,0);
    _display.print("% ");
    _display.display();
    
}