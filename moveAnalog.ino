#include "XInput.h"
#include "helper_3dmath.h"

#define MIN_Y 1600
#define MIN_X 4000
#define INCREMENT 500

bool isMoving;
int16_t lastValue;;

void setupGamepadEmulation()
{
    XInput.begin();
    isMoving = false;
    lastValue = 0;
}

bool manageMotion(int16_t accel)
{

    if (abs(accel) >= MIN_Y)
    {
          digitalWrite(9, HIGH);
          //delay(300);


        if(isMoving && abs(accel) > abs(lastValue)){
            int16_t tmp_accel = XInput.getJoystickY(JOY_LEFT) + INCREMENT;
            XInput.setJoystickY(JOY_LEFT, tmp_accel); //Incrementa velocità
            lastValue = tmp_accel;                   //Saves it
        }
        else if (!isMoving){
            //Start moving
            XInput.setJoystickY(JOY_LEFT, 2000);
            lastValue = 2000; //default
            isMoving = true;
        }
        else{
            XInput.setJoystickY(JOY_LEFT, 0);
            isMoving = false; //stop
            lastValue = 0;
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
