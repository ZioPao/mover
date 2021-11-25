#pragma once

#include "mbed.h"
#include "LM75B.h"
#include "MMA7660.h"

#include "Vector.h"
#include "Utils.h"

template <class Parent>
class FrdmK64f_AppShield_Input : public Parent
{
public: // List of manged Inputs

    enum IDBinaryInput
    {
        JoystickUp,
        JoystickDown,
        JoystickLeft,
        JoystickRight,
        JoystickMiddle,
        IDBinaryInput_MAX
    };
    
    enum IDAnalogInput
    {
        PotLeft,
        PotRight,
        Temp,
        IDAnalogInput_MAX
    };
    
    enum IDVectorInput
    {
        Accel,
        IDVectorInput_MAX
    };

private:
    
    // Joystick
    InterruptIn         _joystickUp;
    InterruptIn         _joystickDown;
    InterruptIn         _joystickLeft;
    InterruptIn         _joystickRight;
    InterruptIn         _joystickMiddle;
    bool                _binaryInputEnable[IDBinaryInput_MAX];
    
    // Potentiometers
    AnalogIn            _potLeft;
    AnalogIn            _potRight;
    float               _potLeftValue;
    float               _potRightValue;

    // Tempeture sensor
    LM75B               _temp;
    float               _tempValue;
    
    bool                _analogInputEnable[IDAnalogInput_MAX];
    float               _analogInputPrec[IDAnalogInput_MAX];
    
    // Accelerometer
    MMA7660             _accel;
    Vector              _accelValue;
    bool                _vectorInputEnable[IDVectorInput_MAX];
    float               _vectorInputPrec[IDVectorInput_MAX];
    
public:

    FrdmK64f_AppShield_Input(void)
        : _joystickUp(A2), _joystickDown(A3), _joystickLeft(A4), _joystickRight(A5), _joystickMiddle(D4),
        _potLeft(A0), _potRight(A1), _potLeftValue(0.0f), _potRightValue(0.0f),
        _temp(D14, D15), _tempValue(0.0f),
        _accel(I2C_SDA, I2C_SCL)
    {
        memset(_binaryInputEnable, 1, sizeof(_binaryInputEnable));
        memset(_analogInputEnable, 0, sizeof(_analogInputEnable));
        memset(_vectorInputEnable, 0, sizeof(_vectorInputEnable));
        
        for (int it = 0; it < IDAnalogInput_MAX; ++it) _analogInputPrec[it] = 100.0f;
        for (int it = 0; it < IDVectorInput_MAX; ++it) _vectorInputPrec[it] = 10.0f;
        
        _joystickUp.rise(this, &FrdmK64f_AppShield_Input::onJoystickUpRise);
        _joystickUp.fall(this, &FrdmK64f_AppShield_Input::onJoystickUpFall);
        _joystickDown.rise(this, &FrdmK64f_AppShield_Input::onJoystickDownRise);
        _joystickDown.fall(this, &FrdmK64f_AppShield_Input::onJoystickDownFall);
        _joystickLeft.rise(this, &FrdmK64f_AppShield_Input::onJoystickLeftRise);
        _joystickLeft.fall(this, &FrdmK64f_AppShield_Input::onJoystickLeftFall);
        _joystickRight.rise(this, &FrdmK64f_AppShield_Input::onJoystickRightRise);
        _joystickRight.fall(this, &FrdmK64f_AppShield_Input::onJoystickRightFall);
        _joystickMiddle.rise(this, &FrdmK64f_AppShield_Input::onJoystickMiddleRise);
        _joystickMiddle.fall(this, &FrdmK64f_AppShield_Input::onJoystickMiddleFall);
        
        _potLeftValue = prec(_potLeft, _analogInputPrec[PotLeft]);
        _potRightValue = prec(_potRight, _analogInputPrec[PotRight]);
        _tempValue = prec(_temp.read(), _analogInputPrec[Temp]);
    }
    
    using   Parent::setEnable;
    void    setEnable(FrdmK64f_AppShield_Input::IDBinaryInput inp, bool act) { _binaryInputEnable[inp] = act; }
    void    setEnable(FrdmK64f_AppShield_Input::IDAnalogInput inp, bool act) { _analogInputEnable[inp] = act; }
    void    setEnable(FrdmK64f_AppShield_Input::IDVectorInput inp, bool act) { _vectorInputEnable[inp] = act; }
    
    using   Parent::setPrecision;
    void    setPrecision(FrdmK64f_AppShield_Input::IDAnalogInput inp, float prec) { _analogInputPrec[inp] = pow(10.0f, prec); }
    void    setPrecision(FrdmK64f_AppShield_Input::IDVectorInput inp, float prec) { _vectorInputPrec[inp] = pow(10.0f, prec); }
    
    // Not interresting section (do not use those methods)
    // Callbacks for joystick
    void    onJoystickUpRise(void) { if (_binaryInputEnable[JoystickUp]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickUp, Event::Rise)); }
    void    onJoystickUpFall(void) { if (_binaryInputEnable[JoystickUp]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickUp, Event::Fall)); }
    void    onJoystickDownRise(void) { if (_binaryInputEnable[JoystickDown]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickDown, Event::Rise)); }
    void    onJoystickDownFall(void) { if (_binaryInputEnable[JoystickDown]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickDown, Event::Fall)); }
    void    onJoystickLeftRise(void) { if (_binaryInputEnable[JoystickLeft]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickLeft, Event::Rise)); }
    void    onJoystickLeftFall(void) { if (_binaryInputEnable[JoystickLeft]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickLeft, Event::Fall)); }
    void    onJoystickRightRise(void) { if (_binaryInputEnable[JoystickRight]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickRight, Event::Rise)); }
    void    onJoystickRightFall(void) { if (_binaryInputEnable[JoystickRight]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickRight, Event::Fall)); }
    void    onJoystickMiddleRise(void) { if (_binaryInputEnable[JoystickMiddle]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickMiddle, Event::Rise)); }
    void    onJoystickMiddleFall(void) { if (_binaryInputEnable[JoystickMiddle]) Parent::_events.push(Event(Event::AppShield, Event::BinaryInput, JoystickMiddle, Event::Fall)); }
    
    // Callback for others sensors
    virtual void    checkAnalog(void)
    {
        Parent::checkAnalog();
        
        if(_analogInputEnable[PotLeft])
        {
            Event   event(Event::AppShield, Event::AnalogInput, PotLeft, prec(_potLeft, _analogInputPrec[PotLeft]));
            if (event.analog != _potLeftValue)
            {
                _potLeftValue = event.analog;
                Parent::_events.push(event);
            }
        }
        
        if(_analogInputEnable[PotRight])
        {
            Event   event(Event::AppShield, Event::AnalogInput, PotRight, prec(_potRight, _analogInputPrec[PotRight]));
            if (event.analog != _potRightValue)
            {
                _potRightValue = event.analog;
                Parent::_events.push(event);
            }
        }
        
        if(_analogInputEnable[Temp])
        {
            Event   event(Event::AppShield, Event::AnalogInput, Temp, prec(_temp.read(), _analogInputPrec[Temp]));
            if (event.analog != _tempValue)
            {
                _tempValue = event.analog;
                Parent::_events.push(event);
            }
        }
    }
    
    void    checkVector(void)
    {
        Parent::checkVector();
        
        if(_vectorInputEnable[Accel])
        {
            Event   event(Event::AppShield, Event::VectorInput, Accel, Vector(prec(_accel.x(), _analogInputPrec[Accel]), prec(_accel.y(), _analogInputPrec[Accel]), prec(_accel.z(), _analogInputPrec[Accel])));
            if (!(event.vector.eq(_accelValue, 1.0f / _analogInputPrec[Accel])))
            {
                _accelValue = event.vector;
                Parent::_events.push(event);
            }
        }
    }
};