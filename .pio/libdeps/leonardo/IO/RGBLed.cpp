#include "RGBLed.h"

RGBLed::RGBLed(PinName pr, PinName pg, PinName pb) : r(pr, 1), g(pg, 1), b(pb, 1) {}