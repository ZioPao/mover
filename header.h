#include "bluetoothLink.h"
#include "xinputMovement.h"
#include "IMUManager.h"
#include "helper_3dmath.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "Wire.h"

//Timer utils is included in another header file (xinputMovement.h)

//////////////////////////////////////////////////

/*Rate of printing debug values in the Serial monitor*/
#define TIMER_PRINTING 100
#define TIMER_MOVEMENT 300        //Necessary to smooth out the Y-AXIS movement, since at "full speed" it would be pretty jittery

//////////////////////////////////////////
/*DEBUG*/
#define ENABLE_IMU
//#define DISABLE_BT_TEST

//////////////////////////////////////////
/*RESET*/
#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {} //definizione della funzione reset
