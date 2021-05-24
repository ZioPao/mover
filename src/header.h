#include "xinputMovement.h"
#include "IMUManager.h"
#include "helper_3dmath.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "Wire.h"
#include "SerialTransfer.h"

//Timer utils is included in another header file (xinputMovement.h)

//////////////////////////////////////////////////

/*Rate of printing debug values in the Serial monitor*/
#define TIMER_PRINTING 300
#define TIMER_MOVEMENT 300         
//////////////////////////////////////////
/*DEBUG*/
#define ENABLE_IMU
#define ENABLE_MANAGER_CONNECTION_TEST
#define DEBUG_LED_PIN 6
//////////////////////////////////////////
/*RESET*/
#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {} //definizione della funzione reset


// addresses


// CMODE 0
// 9600 baud to test
// Master = 98D3,21,F73BF2
// Slave = 98D3,31,F98F5E

