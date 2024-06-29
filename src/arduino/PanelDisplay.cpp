#include "PanelDisplay.h"

void cPanelDisplay::printData(sDataCmd dataIn, sDataCmd dataOut)
{
    _display.clearDisplay();
    _display.setTextSize(2);
    _display.setTextColor(WHITE);

//     _display.setCursor(200,200);
//     _display.print(0);

        //zadana

        _display.setTextSize(1);
        _display.setCursor(0,20);
        _display.print("t:");
        _display.setCursor(0,36);
        _display.print("w:");
        _display.setCursor(0,52);
        _display.print("s:");

        _display.setTextSize(2);
        _display.setCursor(16,0);
        _display.print("Zad.");
        _display.setCursor(72,0);
        _display.print("Zm.");

        //aktualna
  

        _display.setTextSize(2);
        _display.setCursor(16,16);    
        _display.print(dataOut.temp,1);
        _display.setCursor(72,16);
        _display.print(dataIn.temp,1);

//okno
        _display.setCursor(16,32);
        if(dataOut.window < -0.01f)
                _display.print("AUTO");
        else
                _display.print(dataOut.window*100,0);


        //zmierzona
        _display.setCursor(72,32);
        _display.print(dataIn.window*100,0);

        //Swiatlo
        _display.setCursor(16,48);
        _display.print(dataOut.light*100,0);

        //Swiatlo
        _display.setCursor(72,48);
        _display.print(dataIn.light*100,0);


//     _display.print("1\n2\n3\n4\n5\n6\n7\n8");

    _display.display();
    
}