#include <XInput.h>
#include "helper_3dmath.h"

void setupGamepadEmulation(){
    XInput.begin();
}

bool checkMotion(VectorInt16 accel){

    if (abs(accel.x) > 2000){
        sendButton();
    }


}


void sendButton(){
        XInput.press(BUTTON_A);
        XInput.release(BUTTON_A);
}
