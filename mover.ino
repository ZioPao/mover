#include "header.h"

//Setup variables
bool isConnectionEstabilished;

void setup()
{
  isConnectionEstabilished = false;

  setupBluetooth();
  //setupGamepadEmulation();

#ifdef DISABLE_BT_TEST
  setupIMU();
  isConnectionEstabilished = true;
#endif
}

/////////////////////////////////////////

////////////////////////////////////////

void loop()
{

  //BT Connection test

  if (!isConnectionEstabilished)
  {

    if (checkBTConnectionMaster())
    {
      isConnectionEstabilished = true;
      setupIMU();
    }
  }
  else
  {
    //Main loop

    VectorInt16 movement = getRealAcceleration();
    int16_t secondMovementY = getBluetoothData();

    Serial.print("Main value -> ");
    Serial.print(movement.y);
    Serial.println();
    Serial.println();
    Serial.print("Value from slave -> ");
    Serial.print(secondMovementY);
    Serial.println("");
    Serial.println("");
    //manageMotion(movement.y);
    //manageMotion(secondMovementY);
  }
}