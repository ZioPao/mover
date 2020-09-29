#include <XInput.h>
#include "helper_3dmath.h"

#define MIN_Y 8000
#define MIN_X 8000
void setupGamepadEmulation()
{
    XInput.begin();
}

bool checkMotion(VectorInt16 accel)
{

    if (abs(accel.y) > MIN_Y)
    {
        //sendButton();
        Serial.println("Y Movement Detected");
    }
    if (abs(accel.x) > MIN_X ){
        Serial.println("X Movement Detected");
    }
}

void sendButton()
{
    //XInput.press(BUTTON_A);
    //XInput.release(BUTTON_A);
}
