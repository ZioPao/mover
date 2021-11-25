#pragma once

#include "Vector.h"

struct Event
{
    enum Device
    {
        FrdmK64f,
        AppShield
    };
    
    const Device  device;
    
    enum Type // Type of data
    {
        BinaryInput,
        AnalogInput,
        VectorInput
    };
    
    const Type  type; // Type of event
    
    const int   id; // Input identifier
    
    enum ButtonState { Rise, Fall };
    
    const ButtonState   binary; // State of the button if needed
    float               analog; // The value if needed (Analog sensors)
    Vector              vector;// Vector of float if needed (accelerometer)
    
    Event(Device, Type, int, ButtonState);
    Event(Device, Type, int, float);
    Event(Device, Type, int, const Vector &);
    Event(const Event &);
};
