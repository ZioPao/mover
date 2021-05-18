#pragma once

#include "mbed.h"

struct RGBLed
{
   DigitalOut   r;
   DigitalOut   g;
   DigitalOut   b;
   
   RGBLed(PinName, PinName, PinName);
};