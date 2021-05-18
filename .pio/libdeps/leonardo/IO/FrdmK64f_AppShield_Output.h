#pragma once

#include "mbed.h"
#include "C12832.h"

#include "RGBLed.h"

struct FrdmK64f_AppShield_Output
{
    C12832  lcd;
    PwmOut  spkr;
    RGBLed  led;
    
    FrdmK64f_AppShield_Output(void);
};