#include "XInput.h"
#include "helper_3dmath.h"

#define MIN_Y 500
#define MIN_X 4000
#define INCREMENT 500

bool is_moving;
int16_t last_value;

void setupGamepadEmulation()
{
    XInput.begin();
    is_moving = false;
    last_value = 0;
}

bool checkMotion(int16_t accel)
{

    if (!is_moving && abs(accel) >= MIN_Y)
    {
        //Start moving
        XInput.setJoystickY(JOY_LEFT, 2000);
        last_value = 2000; //default
        is_moving = true;
    }
    else if (is_moving && abs(accel >= MIN_Y))
    {
        //keep moving
        if (abs(accel) > last_value)
        {
            int16_t tmp_accel = XInput.getJoystickY(JOY_LEFT) + INCREMENT;
            XInput.setJoystickY(JOY_LEFT, tmp_accel); //Incrementa velocità
            last_value = tmp_accel;                   //Saves it
        }
    }
    else
    {
        XInput.setJoystickY(JOY_LEFT, 0);
        is_moving = false; //stop
    }

    // }
    // }
    // if (abs(accel.y) > MIN_Y)
    // {

    //     XInput.setJoystickY(JOY_LEFT, accel.y * 2);
    //     //sendButton();
    //     //Serial.println("Y Movement Detected");
    // }

    // // if (abs(accel.x) > MIN_X)
    // // {
    // //     XInput.setJoystickX(JOY_LEFT, accel.x * 3);

    // //     //Serial.println("X Movement Detected");
    // // }
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
