#include "bluetoothLink.h"
#include "xinputMovement.h"
#include "IMUManager.h"
#include "helper_3dmath.h"
#include "Wire.h"

//Timer utils is included in another header file (xinputMovement.h)

//////////////////////////////////////////////////

/*Rate of printing debug values in the Serial monitor*/
#define TIMER_PRINTING 500
#define TIMER_MOVEMENT 300        //Necessary to smooth out the Y-AXIS movement, since at "full speed" it would be pretty jittery

//////////////////////////////////////////
/*DEBUG*/
#define ENABLE_IMU
//#define DISABLE_BT_TEST