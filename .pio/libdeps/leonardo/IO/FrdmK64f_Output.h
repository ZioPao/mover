#pragma once

#include "RGBLed.h"

struct FrdmK64f_Output
{
    RGBLed  led;
    Serial  host;
      
    FrdmK64f_Output(void);
};