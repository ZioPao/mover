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
void loop()
{

  //BT Connection test

  if (!isConnectionEstabilished)
  {

    if (checkBTConnectionSlave())
    {
      isConnectionEstabilished = true;
      setupIMU();
    }
  }
  else
  {
    //Main loop
    VectorInt16 movement = getRealAcceleration();

    sendBluetoothData(movement.y);
  }
}