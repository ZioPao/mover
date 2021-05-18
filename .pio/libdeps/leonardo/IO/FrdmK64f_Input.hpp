#pragma once

#include "mbed.h"
#include "FXOS8700Q.h"

template <class Parent>
class FrdmK64f_Input : public Parent
{
public: // List of manged Inputs

    enum IDBinaryInput
    {
        ButtonLeft,
        ButtonRight,
        IDBinaryInput_MAX
    };
    
    enum IDVectorInput
    {
        Accel,
        Magnet,
        IDVectorInput_MAX
    };
    
private:

    // Buttons
    InterruptIn         _buttonLeft;
    InterruptIn         _buttonRight;
    bool                _binaryInputEnable[IDBinaryInput_MAX];
    
    FXOS8700Q_acc       _accel;
    FXOS8700Q_mag       _magnet;
    Vector              _accelValue;
    Vector              _magnetValue;    
    float               _accelPrecision;
    float               _magnetPrecision;
    bool                _vectorInputEnable[IDVectorInput_MAX];
    float               _vectorInputPrec[IDVectorInput_MAX];
    
public:
    FrdmK64f_Input(void)
        : _buttonLeft(SW3), _buttonRight(SW2),
          _accel( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1), _magnet( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1),
          _accelPrecision(100.0f), _magnetPrecision(100.0f)

    {
        memset(_binaryInputEnable, 1, sizeof(_binaryInputEnable));
        memset(_vectorInputEnable, 0, sizeof(_vectorInputEnable));
        
        for (int it = 0; it < IDVectorInput_MAX; ++it) _vectorInputPrec[it] = 10.0f;
        
        _buttonLeft.rise(this, &FrdmK64f_Input::onButtonLeftRise);
        _buttonLeft.fall(this, &FrdmK64f_Input::onButtonLeftFall);
        _buttonRight.rise(this, &FrdmK64f_Input::onButtonRightRise);
        _buttonRight.fall(this, &FrdmK64f_Input::onButtonRightFall);
        
        _accel.enable();
        _magnet.enable();
    }
    
    using   Parent::setEnable;
    void    setEnable(FrdmK64f_Input::IDBinaryInput inp, bool act) { _binaryInputEnable[inp] = act; }
    void    setEnable(FrdmK64f_Input::IDVectorInput inp, bool act) { _vectorInputEnable[inp] = act; }
    
    using   Parent::setPrecision;
    void    setPrecision(FrdmK64f_Input::IDVectorInput inp, float prec) { _vectorInputPrec[inp] = pow(10.0f, prec); }

    // Not interresting section (do not use those methods)
    // Callbacks for joystick
    void    onButtonLeftRise(void) { if (_binaryInputEnable[ButtonLeft]) Parent::_events.push(Event(Event::FrdmK64f, Event::BinaryInput, ButtonLeft, Event::Rise)); }
    void    onButtonLeftFall(void) { if (_binaryInputEnable[ButtonLeft]) Parent::_events.push(Event(Event::FrdmK64f, Event::BinaryInput, ButtonLeft, Event::Fall)); }
    void    onButtonRightRise(void) { if (_binaryInputEnable[ButtonRight]) Parent::_events.push(Event(Event::FrdmK64f, Event::BinaryInput, ButtonRight, Event::Rise)); }
    void    onButtonRightFall(void) { if (_binaryInputEnable[ButtonRight]) Parent::_events.push(Event(Event::FrdmK64f, Event::BinaryInput, ButtonRight, Event::Fall)); }

    using Parent::checkAnalog;    
    // Callback for others sensors
    virtual void    checkVector(void)
    {
        Parent::checkVector();
        
        if(_vectorInputEnable[Accel])
        {
            MotionSensorDataUnits acc_data;
            _accel.getAxis(acc_data);
            Vector   tmp;
            tmp.x = prec(acc_data.x, _vectorInputPrec[Accel]);
            tmp.y = prec(acc_data.y, _vectorInputPrec[Accel]);
            tmp.z = prec(acc_data.z, _vectorInputPrec[Accel]);
            Event   event(Event::FrdmK64f, Event::VectorInput, Accel, tmp);
            if (!(event.vector.eq(_accelValue, 1.0f / _vectorInputPrec[Accel])))
            {
                _accelValue = event.vector;
                Parent::_events.push(event);
            }
        }
        
        if(_vectorInputEnable[Magnet])
        {
            MotionSensorDataUnits mag_data;
            _magnet.getAxis(mag_data);
            Vector   tmp;
            tmp.x = prec(mag_data.x, _vectorInputPrec[Magnet]);
            tmp.y = prec(mag_data.y, _vectorInputPrec[Magnet]);
            tmp.z = prec(mag_data.z, _vectorInputPrec[Magnet]);
            Event   event(Event::FrdmK64f, Event::VectorInput, Magnet, tmp);
            if (!(event.vector.eq(_accelValue, (int)(1.0f / _vectorInputPrec[Magnet]))))
            {
                _accelValue = event.vector;
                Parent::_events.push(event);
            }
        }
    }
};