#include "I2Cdev.h"
#include "helper_3dmath.h"
#include <Wire.h>

///////////////////////////////////////////////////
/*MASTER AND SLAVE MOVER

/*The master will read data from its IMU and get the data from a second Mover.
It'll also do the main calculations necessary to make walk-in-place movement work*/
#define MASTER_MOVER

/*The slave mover will read data from its IMU and send it to the master, 
to let it manage it*/
//#define SLAVE_MOVER

//////////////////////////////////////////////////

void setup()
{

  setupIMU();
  setupBluetooth();
  //setupGamepadEmulation();
}

/////////////////////////////////////////

void loop()
{


  VectorInt16 movement = getRealAcceleration();

#ifdef MASTER_MOVER

  //todo it should be another VectorInt16
  //int16_t secondMovement = getBluetoothData();

  checkMotion(movement);
  
  //checkMotion(secondMovement);
#endif

#ifdef SLAVE_MOVER
  sendBluetoothData(test.x);
#endif

  /*STILL DEBUG STUFF*/

  //printWorldAcceleration();

  // Wire.beginTransmission(2); // transmit to device #4

  //Serial.println(test.x);
  //Wire.write(2);
  //writeInt16(test.x);
  //Wire.endTransmission();    // stop transmitting

  //x++;
  //delay(500);
}
