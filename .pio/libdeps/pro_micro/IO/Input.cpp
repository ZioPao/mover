#include "IO.hpp"

Input::Input(void)
{
    _tickerAnalog.attach(this, &Input::checkAnalog, 0.1);
    _tickerVector.attach(this, &Input::checkVector, 0.3);
}
Input::operator    bool(void) { return (!_events.empty()); }

Event   Input::pull(void)
{
    Event   event = _events.front();
    
    _events.pop();
    return (event);
}

void    Input::setAnalogSampleSpeed(float time) { _tickerAnalog.attach(this, &Input::checkAnalog, time); }
void    Input::setVectorSampleSpeed(float time) { _tickerVector.attach(this, &Input::checkVector, time); }

void    Input::setEnable(void) {}
void    Input::setPrecision(void) {}

void    Input::checkAnalog(void) {}
void    Input::checkVector(void) {}

