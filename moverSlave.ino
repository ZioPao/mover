#include "header.h"

//Setup variables
bool isConnectionEstabilished;

//Timer stuff
MiniTimer timerPrinting;

//Acceleration variables
int16_t fMov;

//Components
XinputMovement xinputMovement;
BluetoothLink bluetoothLink;
IMUManager imuManager;

void setup()
{
  isConnectionEstabilished = false;
  imuManager.setup();

  fMov = 0;

  //Timer setup
  timerPrinting.setup(TIMER_PRINTING);

#ifdef DISABLE_BT_TEST
  isConnectionEstabilished = true;
#endif
}

/////////////////////////////////////////
void printValues()
{
  Serial.print("Main value -> ");
  Serial.print(fMov);

  Serial.print("   ");
  Serial.println();
}
/////////////////////////////////////////
void loop()
{

  //BT Connection test

  if (!isConnectionEstabilished)
  {

    if (bluetoothLink.checkConnectionSlave())
    {
      isConnectionEstabilished = true;
    }
  }
  else
  {
    //Main loop

    if (timerPrinting.update())
    {
      printValues();
    }
    fMov = imuManager.getRealAcceleration();

    bluetoothLink.sendData(fMov);
  }
}