#include "bluetoothLink.h"
#include "xinputMovement.h"
#include "helper_3dmath.h"
#include "timer.h"
#include "Wire.h"


///////////////////////////////////////////////////
/*MASTER AND SLAVE MOVER

/*The master will read data from its IMU and get the data from a second Mover.
It'll also do the main calculations necessary to make walk-in-place movement work*/
#define MASTER_MOVER

/*The slave mover will read data from its IMU and send it to the master, 
to let it manage it*/
//#define SLAVE_MOVER

//////////////////////////////////////////////////


//////////////////////////////////////////
/*DEBUG*/

#define DISABLE_BT_TEST