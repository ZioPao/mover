#pragma once

#include <queue>

#include "mbed.h"

#include "Vector.h"
#include "Event.h"

class Input
{
    Ticker              _tickerAnalog;
    Ticker              _tickerVector;

protected:
    // List of queued events
    std::queue<Event>   _events;
    
public:
    Input(void);
    
    operator    bool(void); // Return if there is an event
    Event       pull(void); // Return the event
    
    void        setAnalogSampleSpeed(float); // Sample speed for analog sensors (potentiometer, temperature, ...)
    void        setVectorSampleSpeed(float); // Sample speed for vector sensors (accelerometer, magnetometer, ...)

    // For inheritance purpose (doesn't do anything)
    void            setEnable(void);
    void            setPrecision(void);
    virtual void    checkAnalog(void);
    virtual void    checkVector(void);
};