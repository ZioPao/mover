#include "I2Cdev.h"
#include "helper_3dmath.h"
#include <Wire.h>

void setup()
{
  //Wire.begin();
  setupIMU();
  setupBluetooth();
  //setupGamepadEmulation();

}

/*Master mover should read data from another mover and do all the calculations.
 The other one should only send data to the main one*/
#define MASTER_MOVER
//#define SLAVE_MOVER

byte x = 0;


//Main methods


/////////////////////////////////////////
void loop()
{
   
  #ifdef SLAVE_MOVER
    VectorInt16 test = getRealAcceleration();
    sendBluetoothData(test.x);
  #endif



  #ifdef MASTER_MOVER
    int16_t t  = getBluetoothData();
    Serial.println(t);
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
