#include "XInput.h"
#include "helper_3dmath.h"

#define MIN_Y 4000
#define MIN_X 4000
void setupGamepadEmulation()
{
    XInput.begin();
}

bool checkMotion(VectorInt16 accel)
{

    if (abs(accel.y) > MIN_Y)
    {

        XInput.setJoystickY(JOY_LEFT, accel.y * 2);
        //sendButton();
        //Serial.println("Y Movement Detected");
    }
    if (abs(accel.x) > MIN_X)
    {
        XInput.setJoystickX(JOY_LEFT, accel.x * 3);

        //Serial.println("X Movement Detected");
    }
}

void moveAnalogStick(int16_t x, int16_t y)
{

    XInput.setJoystick(JOY_LEFT, x, y);
}

/*Test methods*/

void sendButton()
{
    //XInput.press(BUTTON_A);
    //XInput.release(BUTTON_A);
}
