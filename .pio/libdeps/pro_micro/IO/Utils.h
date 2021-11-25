#pragma once

#include <math.h>

inline double   prec(double val, double mult) { return (ceil(val * mult) / mult); }