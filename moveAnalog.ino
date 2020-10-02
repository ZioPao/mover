#include "XInput.h"
#include "helper_3dmath.h"

#define MIN_Y 1600
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

bool manageMotion(int16_t accel)
{

    if (abs(accel) >= MIN_Y)
    {
          digitalWrite(9, HIGH);
          //delay(300);


        if(is_moving && abs(accel) > abs(last_value)){
            int16_t tmp_accel = XInput.getJoystickY(JOY_LEFT) + INCREMENT;
            XInput.setJoystickY(JOY_LEFT, tmp_accel); //Incrementa velocità
            last_value = tmp_accel;                   //Saves it
        }
        else if (!is_moving){
            //Start moving
            XInput.setJoystickY(JOY_LEFT, 2000);
            last_value = 2000; //default
            is_moving = true;
        }
        else{
            XInput.setJoystickY(JOY_LEFT, 0);
            is_moving = false; //stop
            last_value = 0;
        }
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
