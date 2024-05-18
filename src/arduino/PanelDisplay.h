#pragma once
#include "display.h"

#include "struct.h"

class cPanelDisplay : public cDisplay
{
public: 
    void printData(sDataCmd dataIn, sDataCmd dataOut);
};